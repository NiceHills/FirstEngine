#pragma once

#include "FirstEngine/Core.h"
#include "FirstEngine/Events/Event.h"

namespace FirstEngine {

	class FE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach(){}
		virtual void OnDetach(){}
		virtual void OnUpdate(){}
		virtual void OnImGuiRender(){};
		virtual void OnEvent(Event& event){}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}