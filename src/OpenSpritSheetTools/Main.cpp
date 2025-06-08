#include <QApplication>
#include <OpenSpritSheetTools/Gui/MainWindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("open-sprite-sheet-tools");
    a.setApplicationDisplayName("Open Sprite Sheet Tools");
    a.setApplicationVersion("0.0.1");
    a.setOrganizationName("brainstream");
    MainWindow w;
    w.show();
    return a.exec();
}
