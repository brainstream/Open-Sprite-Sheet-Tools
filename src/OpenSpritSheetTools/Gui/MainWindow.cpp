#include <OpenSpritSheetTools/Gui/SpriteSheetSplitterWidget.h>
#include <OpenSpritSheetTools/Gui/MainWindow.h>
#include <OpenSpritSheetTools/Settings.h>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *_parent) :
    QMainWindow(_parent)
{
    setupUi(this);
    QSettings settings;
    restoreGeometry(settings.value(gc_settings_key_wnd_geom).toByteArray());
    restoreState(settings.value(gc_settings_key_wnd_state).toByteArray());
}

void MainWindow::closeEvent(QCloseEvent * _event)
{
    QSettings settings;
    settings.setValue(gc_settings_key_wnd_geom, saveGeometry());
    settings.setValue(gc_settings_key_wnd_state, saveState());
}

void MainWindow::showSheetSplitter()
{
    SpriteSheetSplitterWidget * splitter_widget = new SpriteSheetSplitterWidget(this);
    int tab = mp_tabs->addTab(splitter_widget, tr("Split Sprite Sheet"));
    connect(splitter_widget, &SpriteSheetSplitterWidget::sheetLoaded, this, [this, tab](const QString & _filename) {
        QFileInfo fi(_filename);
        mp_tabs->setTabText(tab, tr("Splitting: %1").arg(fi.fileName()));
    });
    mp_tabs->setCurrentIndex(tab);
}

void MainWindow::closeTab(int _index)
{
    mp_tabs->widget(_index)->deleteLater();
}
