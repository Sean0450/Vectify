#include <QtWidgets>

#include "Controller/Controller.h"
#include "View/DocumentControlBar.h"
#include "View/FiguresToolBar.h"
#include "View/PropertiesToolBar.h"
#include "View/View.h"
#include "View/WorkAreaWidget.h"

int main(int argc, char * argv[])
{
  QApplication a(argc, argv);
  auto mainWindow = std::make_shared<View>();
  auto controller = Controller::Create(mainWindow);
  std::weak_ptr<Controller> weakController(controller);

  mainWindow->GetDocumentControlBar()->SetObserver(weakController);
  mainWindow->GetFiguresToolBar()->SetObserver(weakController);
  mainWindow->GetPropertiesToolBar()->SetObserver(weakController);
  mainWindow->GetWorkArea()->SetObserver(weakController);
  mainWindow->show();

  return a.exec();
}
