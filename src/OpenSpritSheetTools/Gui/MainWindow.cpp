/**********************************************************************************************************
 * Copyright © 2025 Sergey Smolyannikov aka brainstream                                                   *
 *                                                                                                        *
 * This file is part of the Open Sprite Sheet Tools.                                                      *
 *                                                                                                        *
 * Open Sprite Sheet Tools is free software: you can redistribute it and/or modify it under  the terms of *
 * the GNU General Public License as published by the Free Software Foundation, either version 3 of the   *
 * License, or (at your option) any later version.                                                        *
 *                                                                                                        *
 * Open Sprite Sheet Tools is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;   *
 * without even the implied warranty of  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.             *
 * See the GNU General Public License for more details.                                                   *
 *                                                                                                        *
 * You should have received a copy of the GNU General Public License along with MailUnit.                 *
 * If not, see <http://www.gnu.org/licenses/>.                                                            *
 *                                                                                                        *
 **********************************************************************************************************/

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
