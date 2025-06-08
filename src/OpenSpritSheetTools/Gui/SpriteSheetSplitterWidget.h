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

#include "ui_SpriteSheetSplitterWidget.h"

class SpriteSheetSplitterWidget : public QWidget, private Ui::SpriteSheetSplitterWidget
{
    Q_OBJECT

public:
    explicit SpriteSheetSplitterWidget(QWidget *parent = nullptr);
    ~SpriteSheetSplitterWidget() override;

signals:
    void sheetLoaded(const QString & _filename);

private slots:
    void openTexture();
    void updatePreview();

private:
    void loadImage(const QString & _path);

private:
    QString m_open_image_dialog_filter;
    QPixmap * mp_pixmap;
    QPen m_sheet_pen;
    QPen m_sprite_pen;
    QBrush m_sprite_brush;
};
