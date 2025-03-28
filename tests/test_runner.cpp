#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

int main(int argc, char **argv) {
  // Create the doctest context and set the options
  doctest::Context context;

  // Apply the command line arguments (e.g., for filtering, options, etc.)
  context.applyCommandLine(argc, argv);

  // Set options for no version, enabling colors, and console reporter
  context.setOption("no-version", true);
  context.setOption("no-colors", false);
  context.setOption("reporters", "console");

  // Run the tests
  return context.run();
}
