#include "fepch.h"
#include "LayerStack.h"

namespace FirstEngine {

	LayerStack::LayerStack()
	{
	}


	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}


	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_LayerInsertIndex + begin(), layer);
		m_LayerInsertIndex++;
	}


	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}


	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(begin(), end(), layer);
		if (it != end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}


	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(begin(), end(), overlay);
		if (it != end())
		{
			m_Layers.erase(it);
		}
	}
}
