#ifndef _CEF_EVENT_H
#define _CEF_EVENT_H

#include <list>

#include "include/base/cef_bind.h"
#include "include/cef_app.h"
#include "include/cef_render_process_handler.h"
#include "include/cef_runnable.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"

#include "cefcontextprovider.h"
#include "cefdebug.h"
#include "ceftypes.h"

extern void logoutf(const char *fmt, ...);

class InexorCefCallback
{

    public:
        InexorCefCallback(CefRefPtr<CefV8Value> callback, CefRefPtr<CefV8Context> context) : callback(callback), context(context) { };

        // Returns handlers
        CefRefPtr<CefV8Value> GetCallbackFunction() { return callback; };
        CefRefPtr<CefV8Context> GetCallbackContext() { return context; };

    private:
        CefRefPtr<CefV8Value> callback;
        CefRefPtr<CefV8Context> context;

        IMPLEMENT_REFCOUNTING(InexorCefCallback);

};

class InexorCefEvent
{

    public:
        InexorCefEvent(CefString name) {
            this->name = name;
        }

        CefString GetName() { return name; }
        void AddCallback(InexorCefCallback *callback) { this->callbacks.push_back(callback); }
        void FireEventWithContext(const InexorCefValueList& arguments);
        void FireEvent(const CefV8ValueList& arguments);

    private:
        CefString name;
        std::list<InexorCefCallback*> callbacks;

        void ConvertArgumentsAndExecuteCallbackWithContext(CefRefPtr<CefV8Value> callback_function, CefRefPtr<CefV8Context> callback_context, const InexorCefValueList& arguments);
        void ExecuteCallbackWithContext(CefRefPtr<CefV8Value> callback_function, CefRefPtr<CefV8Context> context, const CefV8ValueList& arguments);
        void ExecuteCallback(CefRefPtr<CefV8Value> callback_function, const CefV8ValueList& arguments);

        IMPLEMENT_REFCOUNTING(InexorCefEvent);
};

#endif  // _CEF_EVENT_H
