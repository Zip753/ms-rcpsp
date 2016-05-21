require 'scanf'

filename = ARGV[0]
dir = File.dirname(filename)
base = File.basename(filename)

sol_lines = IO.readlines(filename)
sol_lines.shift

all = []

sol_lines.each do |line|
  fst = true
  time = 0
  line.block_scanf("%d-%d") do |x|
    if fst
      time = x[0]
      fst = false
    else
      ires = x[0]
      itask = x[1]

      all << {
        start: time,
        res: ires,
        task: itask
      }
    end
  end
end

puts all

/^(?<def_name>\w+)\./ =~ base
ndef_name = File.join(dir, "#{def_name}.ndef")
ndef_lines = IO.readlines(ndef_name)

/^(?<ntask>\d+)\s+(?<nres>\d+)$/ =~ ndef_lines[0]

duration = {}

ndef_lines[(nres.to_i + 1)..-1].each do |line|
  /^(?<task_id>\d+)\s+(?<dur>\d+)/ =~ line
  duration[task_id.to_i] = dur.to_i
end

puts duration

js_data = all.sort {|a, b| a[:res] <=> b[:res]}.map do |d|
  fin = d[:start] + duration[d[:task]]
  "[ '#{d[:res]}', '#{d[:task]}', '#{d[:start]} - #{fin}', new Date(2010, 0, #{d[:start]}), new Date(2010, 0, #{fin + 1}) ]"
end.join(",\n")

html = <<-HTML
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
        dataTable.addRows([#{js_data}]);

        chart.draw(dataTable);

        var height = document.querySelector("#timeline div:first-child div:first-child div:first-child div svg").height.baseVal.value + 70;

        chart.draw(dataTable, {height: height});

      }
    </script>
  </head>
  <body>
    <div id="timeline"></div>
  </body>
</html>
HTML

IO.write(File.join(dir, "#{base}.html"), html)