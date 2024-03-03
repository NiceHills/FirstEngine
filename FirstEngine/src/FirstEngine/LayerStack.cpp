#include "fepch.h"
#include "LayerStack.h"

namespace FirstEngine {

	LayerStack::LayerStack()
	{
		m_LayerInsert = begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}


	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
		m_LayerInsert++;
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
			//m_LayerInsert--;
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