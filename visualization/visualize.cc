#include <cstring>
#include <fstream>
#include <memory>
#include <sstream>

#include "google_timeline.h"
#include "palletizer.h"
#include "renderer.h"
#include "timeslot_table.h"
#include "visualizer.h"

int main(int argc, char* argv[]) {
  std::ostringstream usage;
  usage << "Create HTML visualization from schedule definition and solution.\n"
        << argv[0] << " def_file sol_file html_file method [--critical]\n\n"
        << "def_file    Project definition file\n"
        << "sol_file    Solution file with schedule\n"
        << "html_file   Output HTML file with visualization\n"
        << "method      Visualization method, one of 'google' or 'table'\n"
        << "               'google' - Javascript Google Timeline chart\n"
        << "               'table'  - HTML Timeslot Table chart\n"
        << "--critical  If enabled, marks tasks on critical path with grey "
            "color\n";

  if (argc < 5 || argc > 6) {
    std::cerr << usage.str();
    return 1;
  }

  bool table = false;
  if (strcmp(argv[4], "table") == 0) {
    table = true;
  } else if (strcmp(argv[4], "google") != 0) {
    std::cerr << usage.str();
    return 1;
  }

  bool critical = false;
  if (argc == 6) {
    if (strcmp(argv[5], "--critical") != 0) {
      std::cerr << usage.str();
      return 1;
    }
    critical = true;
  }

  std::ifstream def(argv[1]);
  std::ifstream sol(argv[2]);
  std::ofstream vis(argv[3]);

  Palletizer palletizer;
  std::unique_ptr<Renderer> renderer = nullptr;
  if (table) {
    renderer = std::make_unique<TimeslotTable>(&palletizer, critical);
  } else {
    renderer = std::make_unique<GoogleTimeline>(&palletizer, critical);
  }
  Visualizer visualizer(renderer.get());

  auto result = visualizer.Visualize(def, sol, vis);
  if (result.first) {
    std::cout << "Visualization success\n";
  } else {
    std::cout << "Visualization fail\n" << result.second << "\n";
  }

  return 0;
}
