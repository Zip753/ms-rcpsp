#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <utility>
#include <vector>

struct assignment {
  int task_id;
  int start_time;
  bool critical;
};

typedef std::map<int, std::vector<assignment>> assignments_map;
typedef std::multimap<int, assignment*> schedule_map;

bool CheckCriticalPath(assignment *assignment, schedule_map* schedule) {
  if (assignment->critical || assignment->start_time <= 1) {
    return assignment->critical = true;
  }
  auto range = schedule->equal_range(assignment->start_time - 1);
  for (auto& a = range.first; a != range.second; ++a) {
    if (CheckCriticalPath(a->second, schedule)) {
      assignment->critical = true;
    }
  }
  schedule->erase(range.first, range.second);
  return assignment->critical;
}

void BuildCriticalPaths(assignments_map* assignments,
                        const std::map<int, int>& duration) {
  // Map finish time to references to assignments
  std::multimap<int, assignment*> schedule;

  int max_finish = 0;
  for (auto& res : *assignments) {
    for (auto& a : res.second) {
      int finish = a.start_time + duration.at(a.task_id);
      schedule.insert({finish, &a});
      if (max_finish < finish)
        max_finish = finish;
    }
  }

  auto range = schedule.equal_range(max_finish);
  for (auto& a = range.first; a != range.second; ++a) {
    CheckCriticalPath(a->second, &schedule);
  }
}

std::string GetColor(size_t idx, size_t size) {
  size_t rounds = (size - 1) / 3 + 1;
  size_t round = idx / 3;
  size_t main_color = 255;
  if (round * 2 > rounds) {
    main_color = 255 * 2 * (rounds - round) / rounds;
  }
  size_t support_color = 255;
  if (round * 2 < rounds) {
    support_color = 255 * 2 * round / rounds;
  }
  size_t zero_color = 0;
  std::ostringstream color("'#", std::ostringstream::ate);
  color << std::hex << std::setfill('0');
  if (idx % 3 == 0) {  // main - red, support - green
    color
        << std::setw(2) << main_color
        << std::setw(2) << support_color
        << std::setw(2) << zero_color;
  } else if (idx % 3 == 1) {  // main - green, support - blue
    color
        << std::setw(2) << zero_color
        << std::setw(2) << main_color
        << std::setw(2) << support_color;
  } else {  // main - blue, support - red
    color
        << std::setw(2) << support_color
        << std::setw(2) << zero_color
        << std::setw(2) << main_color;
  }
  color << "'";
  return color.str();
}

std::pair<bool, std::string> Visualize(std::ifstream& def,
                                       std::ifstream& sol,
                                       std::ofstream& vis) {
  std::string line;
  do {
    if (!std::getline(def, line)) return {false, "Wrong .def format"};
  } while (line != "TaskID \t Duration \t Skill \t Predecessor IDs ");

  // Read task IDs and durations
  std::smatch match;
  std::regex pattern("^(\\d+)\\s+(\\d+)");
  std::map<int, int> duration;
  while (std::getline(def, line)) {
    if (!std::regex_search(line, match, pattern)) break;
    int task_id = std::stoi(match[1]);
    int task_duration = std::stoi(match[2]);
    duration[task_id] = task_duration;
  }

  // Read first line with headers
  if (!std::getline(sol, line)) return {false, "Missing .sol header"};
  // Read task assignments
  std::map<int, std::vector<assignment>> assignments;
  while (std::getline(sol, line)) {
    // Read start time
    pattern = "(\\d+)";
    if (!std::regex_search(line, match, pattern)) {
      return {false, "Missing start time"};
    }
    int start_time = std::stoi(match[1]);
    // Read assignments
    line = match.suffix();
    pattern = "(\\d+)-(\\d+)";
    while (std::regex_search(line, match, pattern)) {
      int resource_id = stoi(match[1]);
      int task_id = stoi(match[2]);
      assignments[resource_id].push_back({task_id, start_time, false});
      line = match.suffix();
    }
  }

  BuildCriticalPaths(&assignments, duration);

  // Convert to Google Timeline definition
  std::ostringstream data;
  std::ostringstream colors;
  size_t idx = 0;
  for (auto& res : assignments) {
    std::string res_color = GetColor(idx++, assignments.size());
    for (auto& a : res.second) {
      int finish_time = a.start_time + duration[a.task_id];
      data << "[ 'Resource " << res.first << "', '" << a.task_id
           << "', '[Task " << a.task_id << "] " << a.start_time << " - "
           << finish_time << "', new Date(2010, 0, " << a.start_time
           << "), new Date(2010, 0, " << (finish_time + 1) << ") ],\n";

      if (a.critical) {
        colors << "'#000000'";
      } else {
        colors << res_color;
      }
      colors << ",";
    }
  }

  vis << R"HTML(
  <html>
    <head>
      <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
    </head>
    <body>
      <div id="timeline"></div>
      <script type="text/javascript">
        google.charts.load('current', {'packages':['timeline']});
        google.charts.setOnLoadCallback(drawChart);
        function drawChart() {
          var container = document.getElementById('timeline');
          var chart = new google.visualization.Timeline(container);
          var dataTable = new google.visualization.DataTable();

          dataTable.addColumn({ type: 'string', id: 'Resource' });
          dataTable.addColumn({ type: 'string', id: 'Name' });
          dataTable.addColumn({ type: 'string', role: 'tooltip' });
          dataTable.addColumn({ type: 'date', id: 'Start' });
          dataTable.addColumn({ type: 'date', id: 'End' });
          dataTable.addRows([)HTML" << data.str() << R"HTML(]);

          chart.draw(dataTable);

          var height = document.querySelector("#timeline div:first-child div:first-child div:first-child svg").height.baseVal.value + 70;

          var options = {
            height: height
            // , timeline: {colorByRowLabel: true}
            // , timeline: {singleColor: '#8d8'}
            , avoidOverlappingGridLines: false
            , hAxis: {textPosition: 'none'}
            , colors: [)HTML" << colors.str() << R"HTML(]
          };

          chart.draw(dataTable, options);

          var parent = document.querySelector('svg');
          var child = parent.children[2];
          // console.log(child);
          parent.removeChild(child);
        }
      </script>
    </body>
  </html>
  )HTML";

  return {true, "OK"};
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " def_file sol_file vis_file\n";
    return 1;
  }

  std::ifstream def(argv[1]);
  std::ifstream sol(argv[2]);
  std::ofstream vis(argv[3]);

  auto result = Visualize(def, sol, vis);
  if (result.first) {
    std::cout << "Visualization success\n";
  } else {
    std::cout << "Visualization fail\n" << result.second << "\n";
  }

  return 0;
}
