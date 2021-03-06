/*
 *   RapCAD - Rapid prototyping CAD IDE (www.rapcad.org)
 *   Copyright (C) 2010-2014 Giles Bathgate
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "fragment.h"
#include "contrib/fragments.h"

Fragment::Fragment()
{
	fragmentNumber=0;
	fragmentSize=2.0;
	fragmentAngle=12.0;
}

Fragment::Fragment(int fn, decimal fs, decimal fa)
{
	fragmentNumber=fn;
	fragmentSize=fs;
	fragmentAngle=fa;
}

int Fragment::getFragments(decimal r)
{
	return get_fragments_from_r(r,fragmentNumber,fragmentSize,fragmentAngle);
}
