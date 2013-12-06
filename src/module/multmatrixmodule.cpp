/*
 *   RapCAD - Rapid prototyping CAD IDE (www.rapcad.org)
 *   Copyright (C) 2010-2013 Giles Bathgate
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

#include "multmatrixmodule.h"
#include "node/transformationnode.h"
#include "context.h"
#include "vectorvalue.h"
#include "numbervalue.h"

MultMatrixModule::MultMatrixModule() : Module("multmatrix")
{
	addParameter("matrix");
}

Node* MultMatrixModule::evaluate(Context* ctx)
{
	VectorValue* matrixVec=dynamic_cast<VectorValue*>(getParameterArgument(ctx,0));

	TransformationNode* n=new TransformationNode();
	n->setChildren(ctx->getInputNodes());

	if(!matrixVec)
		return n;

	int index=0;
	foreach(Value* colVal,matrixVec->getChildren()) {
		VectorValue* rowVal=dynamic_cast<VectorValue*>(colVal);
		if(rowVal) {
			foreach (Value* valueVal, rowVal->getChildren()) {
				NumberValue* value=dynamic_cast<NumberValue*>(valueVal);
				if(value) {
					n->matrix[index]=value->getNumber();
				}
				index++;
				if(index>16)
					return n;
			}
		}
	}

	return n;
}
