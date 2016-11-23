#include "google_timeline.h"

#include <sstream>

std::string GoogleTimeline::GetHTML(
    const Visualizer::assignments_map &assignments) {
  // Convert to Google Timeline definition
  std::ostringstream data;
  std::ostringstream colors;
  for (auto& res : assignments) {
    std::string res_color = "'#" + GetColor() + "'";
    for (auto& a : res.second) {
      data << "[ 'Resource " << res.first << "', '" << a.task_id
           << "', '[Task " << a.task_id << "] " << a.start_time << " - "
           << a.finish_time << "', new Date(2010, 0, " << a.start_time
           << "), new Date(2010, 0, " << (a.finish_time + 1) << ") ],\n";

//      if (a.critical) {
//        colors << "'#000000'";
//      } else {
        colors << res_color;
//      }
      colors << ",";
    }
  }

  std::ostringstream vis;
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
  return vis.str();
}
