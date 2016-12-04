#include "google_timeline.h"

#include <sstream>

std::string GoogleTimeline::GetHTML(
    const Visualizer::assignments_map &assignments) {

  const std::string critical_color("'#000'");

  // Convert to Google Timeline definition
  std::vector<Visualizer::assignment> critical_tasks;
  std::ostringstream data;
  std::ostringstream colors;
  for (auto& res : assignments) {
    for (auto& a : res.second) {
      data << "[ 'Resource " << res.first << "', '" << a.task_id
           << "', '[Task " << a.task_id << "] " << a.start_time << " - "
           << a.finish_time << "', new Date(2010, 0, " << a.start_time
           << "), new Date(2010, 0, " << (a.finish_time + 1) << ") ],\n";

      if (critical() && a.critical) {
        critical_tasks.push_back(a);
        colors << critical_color;
      } else {
        colors << "'#" + GetColor() + "'";
      }
      colors << ",";
    }
  }

  if (!critical_tasks.empty()) {
    for (auto& a : critical_tasks) {
      data << "[ 'Critical path', '" << a.task_id
           << "', '[Task " << a.task_id << "] " << a.start_time << " - "
           << a.finish_time << "', new Date(2010, 0, " << a.start_time
           << "), new Date(2010, 0, " << (a.finish_time + 1) << ") ],\n";
      colors << critical_color << ",";
    }
  }

  std::ostringstream vis;
  vis << R"HTML(
  <html>
    <head>
      <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
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

          var el = document.querySelector("#timeline div:first-child " +
"div:first-child div:first-child div:last-child svg");
          if (el === null) {
            el = document.querySelector("#timeline div:first-child " +
"div:first-child div:first-child svg");
          }
          var height = el.height.baseVal.value + 70;
          console.log(height);

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
          console.log(child);
          parent.removeChild(child);
        }
      </script>
    </head>
    <body>
      <div id="timeline"></div>
    </body>
  </html>
  )HTML";
  return vis.str();
}
