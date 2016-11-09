#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>

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
  struct assignment {
    int task_id;
    int start_time;
  };
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
      assignments[resource_id].push_back({task_id, start_time});
      line = match.suffix();
    }
  }

  // Convert to Google Timeline definition
  std::ostringstream data;
  for (auto& res : assignments) {
    for (auto& a : res.second) {
      int finish_time = a.start_time + duration[a.task_id];
      data << "[ 'Resource " << res.first << "', '" << a.task_id
           << "', '[Task " << a.task_id << "] " << a.start_time << " - "
           << finish_time << "', new Date(2010, 0, " << a.start_time
           << "), new Date(2010, 0, " << (finish_time + 1) << ") ],\n";
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
            , timeline: {colorByRowLabel: true}
            // , timeline: {singleColor: '#8d8'}
            , avoidOverlappingGridLines: false
            , hAxis: {textPosition: 'none'}
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