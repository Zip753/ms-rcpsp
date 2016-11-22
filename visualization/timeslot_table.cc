#include "timeslot_table.h"

#include <sstream>

std::string TimeslotTable::GetHTML(Visualizer::assignments_map &assignments) {
  std::ostringstream styles;
  std::ostringstream table;

  table << "<tr><td class=\"first\"></td>";
  int max_fin = GetMaxFinishTime(assignments);
  for (int i = 0; i <= max_fin; ++i) {
    table << "<td class=\"cell\">" << i << "</td>";
  }
  table << "</tr>\n";

  int cell_width = max_fin >= 100 ? 23 : 16;

  styles << "table { width: " << 90 + cell_width * (max_fin + 1) << "px; }\n";

  std::vector<int> color_set(static_cast<size_t>(max_fin) + 1);
  for (auto& res : assignments) {
    std::fill(color_set.begin(), color_set.end(), -1);
    for (auto& a : res.second) {
      styles << ".color" << a.task_id
             << " { background-color: #" << GetColor() << "; }\n";
      for (int i = a.start_time; i <= a.finish_time; ++i)
        color_set[i] = a.task_id;
    }
    table << "<tr><td class=\"first\">Resource " << res.first << "</td>\n";
    for (int i = 0; i <= max_fin; ++i) {
      table << "<td class=\"cell";
      if (color_set[i] != -1) {
        table << " color" << color_set[i];
      }
      table << "\"></td>";
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
      }
      .first {
        width: 90px;
        text-align: center;
      }
      table, th, td {
        border: 1px solid black;
        border-collapse: collapse;
        font-size: 16px;
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

int TimeslotTable::GetMaxFinishTime(Visualizer::assignments_map &assignments) {
  int max = -1;
  for (auto& res : assignments) {
    for (auto& a : res.second) {
      if (max < a.finish_time)
        max = a.finish_time;
    }
  }
  return max;
}
