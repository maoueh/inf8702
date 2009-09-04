
Logger* Application::getLogger()
{
    return mLogger;
}

void Application::setInstance(HINSTANCE instance) 
{ 
	mInstance = instance;
}

void Application::setWindowProcedure(WNDPROC windowProcedure) 
{ 
	mWindowProcedure = windowProcedure;
}
