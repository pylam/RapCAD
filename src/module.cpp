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

#include "module.h"
#include "context.h"

Module::Module()
{
	scope=NULL;
	auxilary=false;
}

Module::Module(const QString n) : name(n)
{
	scope=NULL;
	auxilary=false;
}

Module::~Module()
{
	foreach(Parameter* p,parameters)
		delete p;

	delete scope;
}

QString Module::getName() const
{
	return name;
}

void Module::setName(QString n)
{
	name=n;
}

bool Module::getAuxilary() const
{
	return auxilary;
}


QList<Parameter*> Module::getParameters() const
{
	return parameters;
}

void Module::setParameters(QList<Parameter*> params)
{
	parameters=params;
}

void Module::setScope(Scope* scp)
{
	scope=scp;
}

Scope* Module::getScope() const
{
	return scope;
}

void Module::accept(TreeVisitor& v)
{
	v.visit(this);
}

Node* Module::evaluate(Context*)
{
	return NULL;
}

void Module::addParameter(QString name)
{
	Parameter* p=new Parameter();
	p->setName(name);
	parameters.append(p);
}

Value* Module::getParameterArgument(Context* ctx, int index)
{
	return getParameterArgument(ctx,index,index);
}

Value* Module::getParameterArgument(Context* ctx, int index, int expectedIndex)
{
	Parameter* p=parameters.at(index);
	return ctx->getArgument(expectedIndex,p->getName());
}
