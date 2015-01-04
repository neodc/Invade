/*!
* \file images.h
* \brief Definition of the Images class.
*/
#ifndef IMAGES_H
#define IMAGES_H
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <map>
#include "../model/unit.h"
#include "../model/side.h"
/*!
 * \brief The Images class.
 * A class that holds all the images used in the UI.
 */
class Images {
		static QImage tile_;
		static QImage tileSelected_;
		static QImage pawn_;
		static QImage A_;
		static QImage B_;
		static QImage Bbomb_;
		static QImage C_;
		static std::map<unsigned, QImage> dice_;
		static std::map<unsigned, QImage> effArrows_;

	public:

		/*!
		 * \brief reload Reloads all the images in the attributes.
		 */
		static void reload();

		/*!
		 * \brief tile Returns a pixmap of a tile of the board.
		 * \param selected Tells if the tile is selected and changes its appearance if so.
		 * \return A pixmap of a tile.
		 */
		static QPixmap tile(bool selected = false);

		/*!
		 * \brief tile Returns a pixmap of a tile with a pawn over it.
		 * \param unit The unit to display over the tile.
		 * \param tileSelected Tells if the tile is selected and changes its appearance if so.
		 * \param unitSelected Tells if the unit is selected and changes its appearance if so.
		 * \return A pixmap of the unit over a tile.
		 */
		static QPixmap tile(Unit unit, bool tileSelected = false, bool unitSelected = false);

		/*!
		 * \brief pawn Returns a pixmap of a generic pawn.
		 * \param type The unit type of the pawn.
		 * \param selected Tells if the unit is selected and changes its appearance if so.
		 * \param side Tells the side of the pawn and changes its appearance depending it.
		 * \return A pixmap of a generic unit.
		 */
		static QPixmap pawn(UnitType type = UnitType::NORMAL, bool selected = false, Side side = Side::NORTH);

		/*!
		 * \brief pawn Returns a pixmap of a unit.
		 * \param unit The unit to display.
		 * \param selected Tells if the unit is selected and changes its appearance if so.
		 * \return A pixmap of the unit.
		 */
		static QPixmap pawn(Unit unit, bool selected = false);

		/*!
		 * \brief dice Returns a pixmap of a dice face.
		 * \param value The value of the dice.
		 * \param selected Tells if the dice is selected and changes its appearance if so.
		 * \return A pixmap of a dice face.
		 */
		static QPixmap dice(unsigned value, bool selected = false);

		/*!
		 * \brief effArrows Returns a pixmap of the arrows telling how dice will be switched.
		 * \param value The value that determines of the dice will change.
		 * \return A pixmap of the arrows.
		 */
		static QPixmap effArrows(unsigned value);

	private:

		static QImage changeImage(QImage origin, int dr, int dg, int db);
};

#endif // IMAGES_H
