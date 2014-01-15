/*
 * Copyright (c) 2013, Roland Bock
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 * 
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "TabSample.h"
#include "MockDb.h"
#include <sqlpp11/select.h>
#include <sqlpp11/insert.h>
#include <sqlpp11/update.h>
#include <sqlpp11/functions.h>

#include <iostream>

DbMock db = {};
DbMock::Printer printer(std::cerr);
SQLPP_ALIAS_PROVIDER_GENERATOR(kaesekuchen);

int main()
{
	TabSample t;

	interpret(t.alpha, printer).flush();
	interpret(t.alpha = 0, printer).flush();
	interpret(t.alpha = sqlpp::tvin(0), printer).flush();
	interpret(t.alpha == 0, printer).flush();
	interpret(t.alpha == sqlpp::tvin(0), printer).flush();
	interpret(t.alpha != 0, printer).flush();
	interpret(t.gamma != sqlpp::tvin(false), printer).flush();
	interpret(t.alpha == 7, printer).flush();
	interpret(t.beta + "kaesekuchen", printer).flush();

	interpret(select(sqlpp::distinct, t.alpha, t.beta), printer).flush();
	interpret(select(sqlpp::distinct, t.alpha, t.beta).from(t), printer).flush();
	interpret(select(sqlpp::distinct, t.alpha, t.beta).from(t).where(t.alpha == 3), printer).flush();
	interpret(select(sqlpp::distinct, t.alpha, t.beta).from(t).where(t.alpha == 3).group_by(t.gamma), printer).flush();
	interpret(select(sqlpp::distinct, t.alpha, t.beta).from(t).where(t.alpha == 3).group_by(t.gamma).having(t.beta.like("%kuchen")), printer).flush();
	interpret(select(sqlpp::distinct, t.alpha, t.beta).from(t).where(t.alpha == 3).group_by(t.gamma).having(t.beta.like("%kuchen")).order_by(t.beta.asc()), printer).flush();
	interpret(select(sqlpp::distinct, t.alpha, t.beta).from(t).where(t.alpha == 3).group_by(t.gamma).having(t.beta.like("%kuchen")).order_by(t.beta.asc()).limit(17).offset(3), printer).flush();

	interpret(parameter(t.alpha), printer).flush();
	interpret(t.alpha == parameter(t.alpha), printer).flush();

	interpret(insert_into(t), printer).flush();
	interpret(insert_into(t).default_values(), printer).flush();
	interpret(insert_into(t).set(t.gamma = true), printer).flush();
	interpret(insert_into(t).set(t.gamma = sqlpp::tvin(false)), printer).flush();

	interpret(update(t), printer).flush();
	interpret(update(t).set(t.gamma = true), printer).flush();

	return 0;
}