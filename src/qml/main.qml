/************************************************************************************
** Simple Media Player, allows to watch videos with simple and uncluttered interface.
** Copyright (C) 2011 Stanislav Ionascu
**
** Contact: Stanislav Ionascu <stanislav.ionascu@gmail.com>
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.

** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************************/

import Qt 4.7;
import com.ionascu.SMP 1.0;

VideoItem {

    id: video;
    source: currentVideo;
    width: 320;
    height: 240;

    onSourceChanged: {
        video.play();
        video.volume = 100;
    }

    onResolutionChanged: {
        window.forceAspectRatio = false;
        if (window.desktopSize.width >= video.resolution.width) {
            video.width = video.resolution.width;
            video.height = video.resolution.height;
        } else {
            video.width = window.desktopSize.width;
            video.height = window.desktopSize.width / video.aspectRatio;
        }
        window.resize(video.width, video.height);
        window.aspectRatio = video.aspectRatio;
        window.forceAspectRatio = true;
    }

    MouseArea {
        anchors.fill: parent;
        onClicked: {
            if (mediaControls.active)
                mediaControls.hide();
            else
                mediaControls.show();
        }
        onDoubleClicked: {
            video.fullscreen = !video.fullscreen;
        }
    }

    MediaControls {
        id: mediaControls;
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        anchors.right: parent.right;
        height: 32;

        duration: video.duration / 1000;
        position: video.position / 1000;

        onSeek: {
            video.position = position * 1000;
        }
    }
}
