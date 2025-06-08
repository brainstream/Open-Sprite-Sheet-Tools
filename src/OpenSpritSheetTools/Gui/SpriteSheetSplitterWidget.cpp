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
#include <OpenSpritSheetTools/Settings.h>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImageReader>
#include <QFileDialog>
#include <QMessageBox>

SpriteSheetSplitterWidget::SpriteSheetSplitterWidget(QWidget *parent) :
    QWidget(parent),
    mp_pixmap(new QPixmap()),
    m_sheet_pen(QColor(0, 255, 0, 80)),
    m_sprite_pen(QColor(255, 0, 0, 80)),
    m_sprite_brush(QColor(255, 0, 0, 50))
{
    m_open_image_dialog_filter = QString(tr("All supported image formats (*.%1)"))
        .arg(QImageReader().supportedImageFormats().join(" *."));
    setupUi(this);
    mp_preview->setScene(new QGraphicsScene(mp_preview));
    mp_btn_save_sprites->setEnabled(false);
}

SpriteSheetSplitterWidget::~SpriteSheetSplitterWidget()
{
    delete mp_pixmap;
}

void SpriteSheetSplitterWidget::openTexture()
{
    QSettings settings;
    QString last_dir = settings.value(gc_settings_key_sheet_dir).toString();
    QString filename = QFileDialog::getOpenFileName(this, tr("Open a Sprite Sheet"), last_dir, m_open_image_dialog_filter);
    if(!filename.isEmpty())
    {
        QFileInfo file_info(filename);
        settings.setValue(gc_settings_key_sheet_dir, file_info.absolutePath());
        loadImage(filename);
    }
}

void SpriteSheetSplitterWidget::loadImage(const QString & _path)
{
    if(mp_pixmap->load(_path))
    {
        mp_edit_texture_size->setText(QString("%1x%2").arg(mp_pixmap->width()).arg(mp_pixmap->height()));
        mp_edit_texture_file->setText(_path);
        mp_spin_rows->setValue(0);
        mp_spin_columns->setValue(0);
        mp_spin_sprite_width->setValue(0);
        mp_spin_sprite_height->setValue(0);
        mp_spin_vspacing->setValue(0);
        mp_spin_hspacing->setValue(0);
        mp_spin_margin_left->setValue(0);
        mp_spin_margin_top->setValue(0);
        mp_tabs_source->setEnabled(true);
        updatePreview();
        emit sheetLoaded(_path);
    }
    else
    {
        QMessageBox::warning(this, nullptr, tr("Unable to load texture"));
    }
}

void SpriteSheetSplitterWidget::updatePreview()
{
    QGraphicsScene * scene = mp_preview->scene();
    scene->clear();
    QGraphicsPixmapItem * pixmap_item = scene->addPixmap(*mp_pixmap);
    scene->addRect({pixmap_item->pos(), mp_pixmap->size()}, m_sheet_pen);
    bool is_valid = forEachRect([this, scene](int __x, int __y, int __width, int __height) {
        scene->addRect(__x, __y, __width, __height, m_sprite_pen, m_sprite_brush);
    });
    mp_btn_save_sprites->setEnabled(is_valid);
}

bool SpriteSheetSplitterWidget::forEachRect(std::function<void(int, int, int, int)> _cb) const
{
    const int rows = mp_spin_rows->value();
    const int columns = mp_spin_columns->value();
    const int sprite_width = mp_spin_sprite_width->value();
    const int sprite_height = mp_spin_sprite_height->value();
    int margin_left = mp_spin_margin_left->value();
    int margin_top = mp_spin_margin_top->value();
    int horizontal_spacing = mp_spin_hspacing->value();
    int vertical_spacing = mp_spin_vspacing->value();
    if(margin_left < 0) margin_left = 0;
    if(margin_top < 0) margin_top = 0;
    if(horizontal_spacing < 0) horizontal_spacing = 0;
    if(vertical_spacing < 0) vertical_spacing = 0;
    if(rows <= 0 || columns <= 0 || sprite_width <= 0 || sprite_height <= 0)
    {
        return false;
    }
    for(quint32 row = 0; row < rows; ++row)
    {
        int y = margin_top + row *sprite_height + row * vertical_spacing;
        for(quint32 col = 0; col < columns; ++col)
        {
            int x = margin_left + col * sprite_width + col * horizontal_spacing;
            _cb(x, y, sprite_width, sprite_height);
        }
    }
    return true;
}

void SpriteSheetSplitterWidget::saveSprites()
{
    QSettings settings;
    QString last_dir = settings.value(gc_settings_key_split_dir, gc_settings_key_sheet_dir).toString();
    QString dir_path = QFileDialog::getExistingDirectory(this, QString(), last_dir);
    if(dir_path.isEmpty())
    {
        return;
    }
    QDir dir(dir_path);
    settings.setValue(gc_settings_key_split_dir, dir.absolutePath());
    QFileInfo fi(mp_edit_texture_file->text());
    QString format = dir.filePath(QString("%1_%2.png").arg(fi.baseName()).arg("%1"));
    int idx = 1;
    forEachRect([this, &idx, &format](int __x, int __y, int __width, int __height) {
        QImage img(__width, __height, QImage::Format_ARGB32);
        img.fill(0);
        QPainter painter(&img);
        painter.drawPixmap(0, 0, *mp_pixmap, __x, __y, __width, __height);
        img.save(format.arg(idx++, 4, 10, QChar('0')));
    });
}
