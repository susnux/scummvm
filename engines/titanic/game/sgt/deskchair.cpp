/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "titanic/game/sgt/deskchair.h"

namespace Titanic {

BEGIN_MESSAGE_MAP(CDeskchair, CSGTStateRoom)
	ON_MESSAGE(TurnOn)
	ON_MESSAGE(TurnOff)
	ON_MESSAGE(ActMsg)
	ON_MESSAGE(MovieEndMsg)
END_MESSAGE_MAP()

void CDeskchair::save(SimpleFile *file, int indent) {
	file->writeNumberLine(1, indent);
	CSGTStateRoom::save(file, indent);
}

void CDeskchair::load(SimpleFile *file) {
	file->readNumber();
	CSGTStateRoom::load(file);
}

bool CDeskchair::TurnOn(CTurnOn *msg) {
	if (_statics->_v8 == "Closed" && _statics->_v9 == "Closed") {
		setVisible(true);
		_statics->_v9 = "Open";
		_fieldE0 = false;
		_startFrame = 0;
		_endFrame = 16;
		playMovie(0, 16, MOVIE_GAMESTATE);
		playSound("b#8.wav");
	}

	return true;
}

bool CDeskchair::TurnOff(CTurnOff *msg) {
	if (_statics->_v9 == "Open") {
		_statics->_v9 = "Closed";
		_fieldE0 = true;
		_startFrame = 16;
		_endFrame = 32;
		playMovie(16, 32, MOVIE_NOTIFY_OBJECT | MOVIE_GAMESTATE);
		playSound("b#2.wav");
	}

	return true;
}

bool CDeskchair::ActMsg(CActMsg *msg) {
	if (msg->_action == "Smash") {
		setVisible(false);
		_statics->_v9 = "Closed";
		_fieldE0 = true;
		loadFrame(0);
		return true;
	} else {
		return CSGTStateRoom::ActMsg(msg);
	}
}

bool CDeskchair::MovieEndMsg(CMovieEndMsg *msg) {
	if (_statics->_v9 == "Closed")
		setVisible(false);
	return true;
}

} // End of namespace Titanic
