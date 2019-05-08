#include <iostream>

#include <Ultralight/Ultralight.h>
#include <string>
#include <thread>

class MyApp : public ultralight::LoadListener {
	ultralight::RefPtr<ultralight::Renderer> m_shared_renderer;
	ultralight::RefPtr<ultralight::View> m_view;
	bool m_done = false;
public:
	MyApp(const ultralight::RefPtr<ultralight::Renderer>& shared_renderer) : m_shared_renderer(shared_renderer) {
		///
		/// Create our View.
		///
		m_view = m_shared_renderer->CreateView(500, 500, false);

		///
		/// Register our MyApp instance as a load listener so we can handle the
		/// View's OnFinishLoading event below.
		///
		m_view->set_load_listener(this);

		///
		/// Load a string of HTML.
		///
		m_view->LoadURL("https://celeste-search.netlify.com");
	}

	virtual ~MyApp() {}

	void Run() {
		///
		/// Continuously update our Renderer until are done flag is set to true.
		///
		/// @note Calling Renderer::Update handles any pending network requests,
		///       resource loads, and JavaScript timers.
		///
		while (!m_done)
			m_shared_renderer->Update();
	}

	///
	/// Inherited from LoadListener, this event is called when the View finishes
	/// loading a page into the main frame.
	///
	virtual void OnFinishLoading(ultralight::View* caller) {
		///
		/// Render all Views (the default GPUDriver paints each View to an
		/// offscreen Bitmap which you can access via View::Bitmap)
		///
		m_shared_renderer->Render();

		///
		/// Get our View's bitmap and write it to a PNG.
		///
		m_view->bitmap()->WritePNG((std::string("result_") + std::to_string(time(NULL)) + ".png").c_str());

		///
		/// Set our done flag to true to exit the Run loop.
		///
		m_done = true;
	}
};

int main(int argc, char* argv[]) {

	std::cout << "Ultralight View Test" << std::endl;
	ultralight::RefPtr<ultralight::Renderer> shared_renderer = ultralight::Renderer::Create();

	for (int i = 0; i < 100; i++) {
		std::cout << "Load and Render Website " << i << std::endl;
		MyApp app(shared_renderer);
		app.Run();

		shared_renderer->PurgeMemory();

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	

}
