[![codecov](https://codecov.io/gh/DriesDeMaeseneer/TO-Groep/branch/main/graph/badge.svg?token=73GROVMJDY)](https://codecov.io/gh/DriesDeMaeseneer/TO-Groep)
# TO-Groep
Learning Automata en Game Agents


#Qt Installatie
###Mac
Hoe je exact Qt installeert op mac weet ik niet je kan wel naar volgende site gaan en de DMG package downloaden
https://download.qt.io/official_releases/qt/5.12/5.12.10/


###Linux
**wget https://download.qt.io/offici\al_releases/qt/5.12/5.12.10/qt-opensource-linux-x64-5.12.10.run**

**chmod +x  qt-opensource-linux-x64-5.12.10.run**

**./qt-opensource-linux-x64-5.12.10.run**

In installer account aanmaken, tijdens installer en Qt 5.12.10 aanvinken.
In CLion hoort het al juist te staan voor Linux, enkel als hij de packages niet vind moet je jou pad aanpassen naar waar Qt op jou pc is geinstalleerd.

Als je een error Gl/gl.h missing hebt moet je volgende packages installeren.

**sudo apt install mesa-common-dev libglu1-mesa-dev**
