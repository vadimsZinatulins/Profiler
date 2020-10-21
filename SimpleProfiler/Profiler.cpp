#include "Profiler.h"

#include <algorithm>

namespace Benchmark
{
Profiler Profiler::m_instance;

Profiler::Profiler() :
	m_currentSession(nullptr),
	m_profileCount(0)
{
}

Profiler::~Profiler()
{
	if(m_currentSession)
		endSession();
}

void Profiler::beginSession(const std::string &name, const std::string &filePath)
{
	m_outputStream.open(filePath);

	writeHeader();

	m_currentSession = new ProfilerSession{ name };
}

void Profiler::writeProfile(const ProfileResult &result)
{
	if(m_profileCount++ > 0)
		m_outputStream << ",";

	std::string name = result.name;
	std::replace(name.begin(), name.end(), '"', '\'');

	m_outputStream << "{";
	m_outputStream << "\"cat\": \"function\",";
	m_outputStream << "\"dur\":" << (result.end - result.start) << ",";
	m_outputStream << "\"name\": \"" << name << "\",";
	m_outputStream << "\"ph\":\"X\",";
	m_outputStream << "\"pid\": 0,";
	m_outputStream << "\"tid\": " << result.threadId << ",";
	m_outputStream << "\"ts\":" << result.start;
	m_outputStream << "}";

	m_outputStream.flush();
}

void Profiler::endSession()
{
	writeFooter();
	m_outputStream.close();

	delete m_currentSession;
	m_currentSession = nullptr;
	m_profileCount = 0;
}

Profiler &Profiler::getInstance()
{
	return m_instance;
}

void Profiler::writeHeader()
{
	m_outputStream << "{\"otherData\": {}, \"traceEvents\": [";
	m_outputStream.flush();
}

void Profiler::writeFooter()
{
	m_outputStream << "]}";
	m_outputStream.flush();
}

}