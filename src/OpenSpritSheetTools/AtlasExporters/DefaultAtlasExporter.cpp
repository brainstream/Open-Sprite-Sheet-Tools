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

#include <OpenSpritSheetTools/AtlasExporters/DefaultAtlasExporter.h>
#include <OpenSpritSheetTools/Exception.h>
#include <QFile>
#include <QXmlStreamWriter>

void DefaultAtlasExporter::exportToAtlas(
    const Splitter & _splitter,
    const std::filesystem::path & _texture_file,
    const std::filesystem::path & _file)
{
    QFile file(_file);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        throw FileOpenException(_file, FileOpenException::Write);
    }
    QFileInfo texture_info(_texture_file);

    QString base_name = texture_info.baseName();
    QString ext = texture_info.completeSuffix();
    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement("atlas");
    xml.writeAttribute("file", std::filesystem::relative(_texture_file, _file.parent_path()).c_str());
    int idx = 0;
    _splitter.forEachFrame([&xml, &idx, &base_name, &ext](int __x, int __y, int __width, int __height) {
       xml.writeStartElement("frame");
       xml.writeAttribute("name", QString("%1_%2.%3").arg(base_name).arg(++idx, 4, 10, QChar('0')).arg(ext));
       xml.writeAttribute("x", QString::number(__x));
       xml.writeAttribute("y", QString::number(__y));
       xml.writeAttribute("width", QString::number(__width));
       xml.writeAttribute("height", QString::number(__height));
       xml.writeEndElement();
    });
    xml.writeEndElement();
    xml.writeEndDocument();
}
