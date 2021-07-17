#pragma once
#include <string>
#include <Windows.h>

enum class PipeAccess              { Write = 0x40000000 };
enum class PipeSharing             { None = 0 };
enum class PipeCreationDisposition { OpenExisting = 3 };

class NamedPipeClient {
public:
	explicit NamedPipeClient(const std::string& name) noexcept;

	void Open() noexcept;
	void Close() const noexcept;
	void Send(const void* buffer, size_t numBytesToWrite) const noexcept;
	void Call(const auto& structure) noexcept;
private:
	std::string m_name;
	HANDLE m_hPipe;
	static constexpr auto m_format = "\\\\.\\pipe\\";

	PipeAccess m_access = PipeAccess::Write;
	PipeSharing m_shareMode = PipeSharing::None;
	PipeCreationDisposition m_creationDisposition = PipeCreationDisposition::OpenExisting;
};

void NamedPipeClient::Call(const auto& structure) noexcept {
	Open();
	Send(static_cast<const void*>(&structure), sizeof(structure));
	Close();
}