#include <FirstEngine.h>

#include "imgui/imgui.h"

class ExampleLayer : public FirstEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(FirstEngine::VertexArray::Create());


		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.9f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.8f, 0.7f, 0.2f, 1.0f,
		};

		std::shared_ptr<FirstEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(FirstEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		FirstEngine::BufferLayout layout = {
			{FirstEngine::ShaderDataType::Float3, "a_Position"},
			{FirstEngine::ShaderDataType::Float4, "a_Color"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		//Element Buffer
		uint32_t indices[3] = { 0,1,2 };

		std::shared_ptr<FirstEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(FirstEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		//Square-----------------------------------
		m_SquareVA.reset(FirstEngine::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};

		std::shared_ptr<FirstEngine::VertexBuffer> suqareVB;
		suqareVB.reset(FirstEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		suqareVB->SetLayout({
			{FirstEngine::ShaderDataType::Float3, "a_Position"},
			});
		m_SquareVA->AddVertexBuffer(suqareVB);

		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
		std::shared_ptr<FirstEngine::IndexBuffer> suqareIB;
		suqareIB.reset(FirstEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(suqareIB);

		std::string vertexSrc = R"(
			#version 330 core
			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position,1.0f);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			out vec4 color;


			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(new FirstEngine::Shader(vertexSrc, fragmentSrc));

		std::string m_BlueShadervertexSrc = R"(
			#version 330 core
			layout(location=0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position,1.0f);
			}
		)";

		std::string m_BlueShaderfragmentSrc = R"(
			#version 330 core
			out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2,0.3,0.8,1.0);
			}
		)";

		m_BlueShader.reset(new FirstEngine::Shader(m_BlueShadervertexSrc, m_BlueShaderfragmentSrc));

	}

	void OnUpdate() override
	{
		if (FirstEngine::Input::IsKeyPressed(FE_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed;
		else if (FirstEngine::Input::IsKeyPressed(FE_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed;

		if (FirstEngine::Input::IsKeyPressed(FE_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;
		else if (FirstEngine::Input::IsKeyPressed(FE_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed;

		if (FirstEngine::Input::IsKeyPressed(FE_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed;
		else if (FirstEngine::Input::IsKeyPressed(FE_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed;

		FirstEngine::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
		FirstEngine::RenderCommand::Clear();

		m_Camera.SetPositiom(m_CameraPosition);
		m_Camera.SetRotatiom(m_CameraRotation);

		FirstEngine::Renderer::BeginScene(m_Camera);

		FirstEngine::Renderer::Submit(m_BlueShader, m_SquareVA);

		FirstEngine::Renderer::Submit(m_Shader, m_VertexArray);

		FirstEngine::Renderer::EndScene();

	}


	virtual void OnImGuiRender() override
	{

	}


	void OnEvent(FirstEngine::Event& event) override
	{
		FirstEngine::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<FirstEngine::KeyPressedEvent>(BIND_EVENT_FN(ExampleLayer::OnKeyPressed));
	}

	bool OnKeyPressed(FirstEngine::KeyPressedEvent& event)
	{

		return false;
	}

private:
	std::shared_ptr<FirstEngine::Shader> m_Shader;
	std::shared_ptr<FirstEngine::VertexArray> m_VertexArray;

	std::shared_ptr<FirstEngine::Shader> m_BlueShader;
	std::shared_ptr<FirstEngine::VertexArray> m_SquareVA;

	FirstEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;

	float m_CameraMoveSpeed = 0.1f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 0.1f;
};


class Sandbox : public FirstEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

FirstEngine::Application* FirstEngine::CreateApplication()
{
	return new Sandbox();
}
