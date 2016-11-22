#include <fstream>
#include <memory>

#include "google_timeline.h"
#include "palletizer.h"
#include "renderer.h"
#include "visualizer.h"

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " def_file sol_file vis_file\n";
    return 1;
  }

  std::ifstream def(argv[1]);
  std::ifstream sol(argv[2]);
  std::ofstream vis(argv[3]);

  Palletizer palletizer;
  std::unique_ptr<Renderer> renderer =
      std::make_unique<GoogleTimeline>(&palletizer);
  Visualizer visualizer(renderer.get());

  auto result = visualizer.Visualize(def, sol, vis);
  if (result.first) {
    std::cout << "Visualization success\n";
  } else {
    std::cout << "Visualization fail\n" << result.second << "\n";
  }

  return 0;
}
