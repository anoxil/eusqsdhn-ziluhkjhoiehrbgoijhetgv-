#include "common.h"

bool hasEnding(string const &fullString, string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

void saveImage(const char *imdname, Mat *image) {
    // On vérifie le nom rentré par l'utilisateur
    if (!hasEnding(imdname, ENDING)) { // On vérifie que ca se termine bien par .png sinon OpenCV plante
        cout << WARNING << "name provide is not complete, adding \"" << ENDING << "\"." << endl;
        imdname = string(imdname).append(ENDING).c_str();
    }

    cout << INFO << "Saving matrice to " << imdname << " ..." << endl;
    imwrite(imdname, *image); // sauvegarde
}
