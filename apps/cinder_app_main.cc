
#include <frontend/scale_pie_graph_app.h>

using scalepiegraph::frontend::ScalePieGraphApp;

void prepareSettings(ScalePieGraphApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(ScalePieGraphApp, ci::app::RendererGl, prepareSettings)

