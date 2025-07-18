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

#pragma once

#include <OpenSpritSheetTools/Gui/ZoomModel.h>
#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit GraphicsView(QWidget * _parent);
    void setZoomModel(ZoomModel * _model);

protected:
    void drawBackground(QPainter * _painter, const QRectF & _rect) override;
    void wheelEvent(QWheelEvent * _event) override;
    void keyPressEvent(QKeyEvent * _event) override;

private slots:
    void applyZoom(quint32 _zoom);

private:
    void applyColorScheme(Qt::ColorScheme _scheme);

private:
    ZoomModel * m_zoom_model;
};

