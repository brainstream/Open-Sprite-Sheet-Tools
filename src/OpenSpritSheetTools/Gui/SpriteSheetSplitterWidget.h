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
