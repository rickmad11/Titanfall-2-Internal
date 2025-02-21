#pragma once
#include "../Appenders/ColorConsoleAppender.h"
#include "../Init.h"

namespace plog
{
    //////////////////////////////////////////////////////////////////////////
    // ColorConsoleAppender with any Formatter

    template<class Formatter, int instanceId>
    PLOG_LINKAGE_HIDDEN inline Logger<instanceId>& init(Severity maxSeverity, OutputStream outputStream)
    {
        static ColorConsoleAppender<Formatter> appender(outputStream);
        return init<instanceId>(maxSeverity, &appender);
    }

    template<class Formatter>
    inline Logger<PLOG_DEFAULT_INSTANCE_ID>& init(Severity maxSeverity, OutputStream outputStream)
    {
        return init<Formatter, PLOG_DEFAULT_INSTANCE_ID>(maxSeverity, outputStream);
    }
}
