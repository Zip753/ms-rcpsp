#include "timeslot_table.h"

#include <algorithm>
#include <sstream>

std::string TimeslotTable::GetHTML(
    const Visualizer::assignments_map &assignments) {
  std::ostringstream styles;
  std::ostringstream table;

  table << "<tr><td class=\"first text\"></td>";
  int max_fin = GetMaxFinishTime(assignments);
  for (int i = 0; i <= max_fin; ++i) {
    table << "<td class=\"cell\">" << i << "</td>";
  }
  table << "</tr>\n";

  int cell_width = max_fin >= 100 ? 17 : 12;

  styles << "table { width: " << 90 + cell_width * (max_fin + 1) << "px; }\n";

  for (auto& res : assignments) {
    int resource_id = res.first;
    styles << ".color" << resource_id
           << " { background-color: #" << GetColor() << "; }\n";
    std::vector<Visualizer::assignment> tasks(res.second);
    std::sort(tasks.begin(), tasks.end(), [=](auto &a, auto &b) {
      return a.start_time > b.start_time;
    });
    table << "<tr><td class=\"first text\">Resource " << resource_id
          << "</td>\n";
    for (int i = 0; i <= max_fin; ++i) {
      table << "<td class=\"cell";
      if (!tasks.empty() && tasks.back().start_time == i) {
        auto task = tasks.back();
        tasks.pop_back();
        table << " text color" << resource_id << "\""
              << " colspan=\"" << task.finish_time - task.start_time + 1;
        i = task.finish_time;
        table << "\">Task " << task.task_id
              << " [" << task.finish_time - task.start_time << "]</td>";
      } else {
        table << "\"></td>";
      }
    }
    table << "</tr>\n";
  }

  std::ostringstream html;
  html << R"HTML(
  <html>
  <head>
    <style>
      .cell {
        width: )HTML" << cell_width << R"HTML(px;
        text-align: center;
        font-size: 11px;
      }
      .first {
        width: 90px;
      }
      .text {
        text-align: center;
        font-size: 16px;
      }
      table, th, td {
        border: 1px solid black;
        border-collapse: collapse;
      }
      table {
        table-layout: fixed;
      }
      )HTML" << styles.str() << R"HTML(
    </style>
  </head>
  <body>
    <table>
      )HTML" << table.str() << R"HTML(
    </table>
  </body>
  </html>
  )HTML";

  return html.str();
}

int TimeslotTable::GetMaxFinishTime(
    const Visualizer::assignments_map &assignments) {
  int max = -1;
  for (auto& res : assignments) {
    for (auto& a : res.second) {
      if (max < a.finish_time)
        max = a.finish_time;
    }
  }
  return max;
}
