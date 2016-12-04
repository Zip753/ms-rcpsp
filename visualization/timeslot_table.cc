#include "timeslot_table.h"

#include <algorithm>
#include <sstream>

std::string TimeslotTable::GetHTML(
    const Visualizer::assignments_map &assignments) {
  std::ostringstream styles;
  std::ostringstream table;

  table << "<tbody>";
  table << "<tr><td class=\"first text\"></td>";
  int max_fin = GetMaxFinishTime(assignments);
  for (int i = 1; i <= max_fin; ++i) {
    table << "<td class=\"cell\">" << i << "</td>";
  }
  table << "</tr>\n";

  int cell_width = max_fin >= 100 ? 17 : 12;
  int table_width = 93 + (cell_width + 3) * (max_fin + 1);
  int box_margin = 10;

  styles << "table { width: " << table_width << "px; }\n";
  styles << "#box { width: " << table_width + 2 * box_margin << "px; "
         << "margin: " << box_margin << "; }\n";

  std::vector<Visualizer::assignment> critical_tasks;

  for (auto& res : assignments) {
    int resource_id = res.first;
    for (auto& a : res.second) {
      if (critical() && a.critical) {
        critical_tasks.push_back(a);
      } else if (!critical() || !a.critical) {
        styles << ".color" << a.task_id
               << " { background-color: #" << GetColor() << "; }\n";
      }
    }
    std::vector<Visualizer::assignment> tasks(res.second);
    std::sort(tasks.begin(), tasks.end(), [=](auto &a, auto &b) {
      return a.start_time > b.start_time;
    });
    table << "<tr><td class=\"first text\">Resource " << resource_id
          << "</td>\n";
    for (int i = 1; i <= max_fin; ++i) {
      table << "<td class=\"cell";
      if (!tasks.empty() && tasks.back().start_time == i) {
        auto task = tasks.back();
        tasks.pop_back();
        table << " text ";
        if (critical() && task.critical) {
          table << "critical";
        } else {
          table << "color" << task.task_id;
        }
        table << "\" colspan=\"" << task.finish_time - task.start_time + 1;
        i = task.finish_time;
        table << "\">Task " << task.task_id
              << " [" << task.finish_time - task.start_time + 1 << "]</td>";
      } else {
        table << "\"></td>";
      }
    }
    table << "</tr>\n";
  }
  table << "</tbody>";

  if (!critical_tasks.empty()) {
    table << "<tbody><tr><td class=\"first text\">Critical path</td>";
    std::sort(critical_tasks.begin(), critical_tasks.end(),
              [&](auto& a, auto& b) { return a.start_time > b.start_time; });
    for (int i = 1; i <= max_fin; ++i) {
      table << "<td class=\"cell";
      if (!critical_tasks.empty() && critical_tasks.back().start_time == i) {
        auto task = critical_tasks.back();
        critical_tasks.pop_back();
        table << " text critical\" colspan=\""
              << task.finish_time - task.start_time + 1;
        i = task.finish_time;
        table << "\">Task " << task.task_id
              << " [" << task.finish_time - task.start_time + 1 << "]</td>";
      } else {
        table << "\"></td>";
      }
    }
    table << "</tr></tbody>";
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
      #box {
        margin: 10px;
      }
      .first {
        width: 90px;
      }
      .text {
        text-align: center;
        font-size: 16px;
      }
      .critical {
        background-color: #000;
        color: #fff;
        border-color: #000 #fff;
      }
      th, td {
        border: 1px solid black;
      }
      table {
        border-collapse: collapse;
        table-layout: fixed;
      }
      tbody:not(:first-child):before {
        content: '';
        display: table-row;
        height: 15px;
      }
      )HTML" << styles.str() << R"HTML(
    </style>
  </head>
  <body>
    <div id="box">
      <table>
        )HTML" << table.str() << R"HTML(
      </table>
    </div>
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
