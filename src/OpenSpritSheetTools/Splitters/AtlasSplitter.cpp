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

#include <OpenSpritSheetTools/Splitters/AtlasSplitter.h>
#include <OpenSpritSheetTools/Atlas/DefaultAtlasSerializer.h>
#include <OpenSpritSheetTools/Exception.h>

AtlasSplitter::AtlasSplitter(QObject * _parent) :
    Splitter(_parent),
    m_serializer(new DefaultAtlasSerializer())
{
}

void AtlasSplitter::setDataFile(const QString & _file)
{
    bool has_changes = m_atlas != nullptr; // False positive [clang-analyzer-deadcode.DeadStores]
    m_atlas.reset();
    std::unique_ptr<Atlas> atlas(new Atlas);
    try
    {
        m_serializer->deserialize(_file.toStdString(), *atlas);
        m_atlas.swap(atlas);
        has_changes = true;
    }
    catch(const Exception & exception)
    {
        emit error(exception.message());
    }
    if(has_changes)
    {
        emit framesChanged();
    }
}

bool AtlasSplitter::forEachFrame(std::function<void(const Frame &)> _cb) const
{
    if(!m_atlas)
        return false;
    foreach(const Frame & frame, m_atlas->frames)
        _cb(frame);
    return true;
}

qsizetype AtlasSplitter::frameCount() const
{
    return m_atlas ? m_atlas->frames.size() : 0;
}

void AtlasSplitter::reset()
{
    bool has_changes = m_atlas != nullptr;
    m_atlas.reset();
    if(has_changes)
        emit framesChanged();
}
