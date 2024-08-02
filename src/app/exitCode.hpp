#pragma once

namespace App
{
	enum class ExitCode
	{
		ok,
		badArguments,
		failedToConnect,
		connectionLost
	};

	int toInt(ExitCode exitCode);
};
