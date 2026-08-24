#pragma once
#include "Cursor.h"
#include "InputManager.h"
#include "PrepContext.h"

class PrepStageBase
{
protected:
	Cursor* cursor;
	InputManager* input;
	PrepContext* context;
public:

	PrepStageBase(Cursor* arg_cursor, InputManager* arg_input, PrepContext* arg_context)
		: cursor(arg_cursor), input(arg_input), context(arg_context) {}
	virtual ~PrepStageBase() {};

	virtual void Input() = 0;
	virtual bool Update() = 0;
	virtual void Draw() = 0;
	virtual void Sound() = 0;
};

#define PREP_CLASS(className)\
	className(Cursor* arg_cursor, InputManager* arg_input, PrepContext* arg_context);\
	void Input() override;\
	bool Update() override;\
	void Draw() override;\
	void Sound() override;

#define PREP_CONSTRUCTOR(className)\
	className::className(Cursor* arg_cursor, InputManager* arg_input, PrepContext* arg_context)\
		: PrepStageBase(arg_cursor, arg_input, arg_context)

#define PREP_INPUT(className)\
	void className::Input()

#define PREP_UPDATE(className)\
	bool className::Update()
