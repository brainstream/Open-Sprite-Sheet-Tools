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
    m_pixmap(new QPixmap()),
    m_sheet_pen(QColor(0, 255, 0, 80)),
    m_sprite_pen(QColor(255, 0, 0, 80)),
    m_sprite_brush(QColor(255, 0, 0, 50))
{
    m_open_image_dialog_filter = QString(tr("All supported image formats (*.%1)"))
        .arg(QImageReader().supportedImageFormats().join(" *."));
    setupUi(this);
    m_preview->setScene(new QGraphicsScene(m_preview));
    m_btn_save_sprites->setEnabled(false);
    m_grid_splitter = new GridSplitter(this);
    connect(m_spin_rows, &QSpinBox::valueChanged, m_grid_splitter, &GridSplitter::setRowCount);
    connect(m_spin_columns, &QSpinBox::valueChanged, m_grid_splitter, &GridSplitter::setColumnCount);
    connect(m_spin_sprite_width, &QSpinBox::valueChanged, m_grid_splitter, &GridSplitter::setSpriteWidth);
    connect(m_spin_sprite_height, &QSpinBox::valueChanged, m_grid_splitter, &GridSplitter::setSpriteHeight);
    connect(m_spin_margin_left, &QSpinBox::valueChanged, m_grid_splitter, &GridSplitter::setMarginLeft);
    connect(m_spin_margin_top, &QSpinBox::valueChanged, m_grid_splitter, &GridSplitter::setMarginTop);
    connect(m_spin_hspacing, &QSpinBox::valueChanged, m_grid_splitter, &GridSplitter::setHorizontalSpacing);
    connect(m_spin_vspacing, &QSpinBox::valueChanged, m_grid_splitter, &GridSplitter::setVerticalSpacing);
    connect(m_grid_splitter, &Splitter::framesChanged, this, &SpriteSheetSplitterWidget::updatePreview);
}

SpriteSheetSplitterWidget::~SpriteSheetSplitterWidget()
{
    delete m_pixmap;
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
    if(m_pixmap->load(_path))
    {
        m_edit_texture_size->setText(QString("%1x%2").arg(m_pixmap->width()).arg(m_pixmap->height()));
        m_edit_texture_file->setText(_path);
        m_spin_rows->setValue(0);
        m_spin_columns->setValue(0);
        m_spin_sprite_width->setValue(0);
        m_spin_sprite_height->setValue(0);
        m_spin_vspacing->setValue(0);
        m_spin_hspacing->setValue(0);
        m_spin_margin_left->setValue(0);
        m_spin_margin_top->setValue(0);
        m_tabs_source->setEnabled(true);
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
    QGraphicsScene * scene = m_preview->scene();
    scene->clear();
    QGraphicsPixmapItem * pixmap_item = scene->addPixmap(*m_pixmap);
    scene->addRect({pixmap_item->pos(), m_pixmap->size()}, m_sheet_pen);
    bool is_valid = m_grid_splitter->forEachFrame([this, scene](int __x, int __y, int __width, int __height) {
        scene->addRect(__x, __y, __width, __height, m_sprite_pen, m_sprite_brush);
    });
    m_btn_save_sprites->setEnabled(is_valid);
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
    QFileInfo fi(m_edit_texture_file->text());
    QString format = dir.filePath(QString("%1_%2.png").arg(fi.baseName()).arg("%1"));
    int idx = 1;
    m_grid_splitter->forEachFrame([this, &idx, &format](int __x, int __y, int __width, int __height) {
        QImage img(__width, __height, QImage::Format_ARGB32);
        img.fill(0);
        QPainter painter(&img);
        painter.drawPixmap(0, 0, *m_pixmap, __x, __y, __width, __height);
        img.save(format.arg(idx++, 4, 10, QChar('0')));
    });
}
