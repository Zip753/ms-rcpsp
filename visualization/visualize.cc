#include <fstream>
#include <memory>
#include <cstring>

#include "google_timeline.h"
#include "palletizer.h"
#include "renderer.h"
#include "timeslot_table.h"
#include "visualizer.h"

int main(int argc, char* argv[]) {
  if (argc < 4 || argc > 5) {
    std::cerr << "Invalid number of arguments.\n"
              << "Usage: " << argv[0] << " def_file sol_file vis_file "
              << "[--table]\n";
    return 1;
  }

  bool table = false;
  if (argc == 5) {
    if (strcmp(argv[4], "--table") != 0) {
      std::cerr << "Invalid flags.\n"
                << "Usage: " << argv[0] << " def_file sol_file vis_file "
                << "[--table]\n";
      return 1;
    }
    table = true;
  }

  std::ifstream def(argv[1]);
  std::ifstream sol(argv[2]);
  std::ofstream vis(argv[3]);

  Palletizer palletizer;
  std::unique_ptr<Renderer> renderer = nullptr;
  if (table) {
    renderer = std::make_unique<TimeslotTable>(&palletizer);
  } else {
    renderer = std::make_unique<GoogleTimeline>(&palletizer);
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
