#pragma once

class PrepStageBase
{
protected:

public:

	PrepStageBase() {};
	virtual ~PrepStageBase() {};

	virtual void Input() = 0;
	virtual bool Update() = 0;
	virtual void Draw() = 0;
	virtual void Sound() = 0;
};

#define PREP_CLASS(className)\
	className();\
	void Input() override;\
	bool Update() override;\
	void Draw() override;\
	void Sound() override;

#define PREP_CONSTRUCTOR(className)\
	className::className()

#define PREP_INPUT(className)\
	void className::Input()

#define PREP_UPDATE(className)\
	bool className::Update()
