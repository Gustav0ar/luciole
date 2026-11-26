#pragma once

#include "fs/posix_fd.h"
#include "fs/transfer_types.h"

#include <cstdint>
#include <filesystem>
#include <functional>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace luciole::transfer {
  bool removableBlockDevice(const std::filesystem::path& device);
  struct BlockMount {
    dev_t filesystem;
    std::string source;
  };
  // Resolves mountId from mountinfo; sets *found when the mount entry exists even if not block-backed.
  std::optional<BlockMount> blockMount(std::string_view mountinfo, std::uint64_t mountId, bool* found = nullptr);

  // Worker-side operations. Tests can hold a flush, return a delayed I/O error, or supply mountinfo snapshots.
  struct WritebackOps {
    std::function<bool(int, dev_t)> removable = nullptr;
    std::function<void(int)> sync = nullptr;
    std::function<std::string()> mountinfo = nullptr;
  };

  class Writeback {
  public:
    struct Volume {
      Fd directory;
      bool removable = false;
      std::vector<TransferResult*> published;
      std::optional<FileError> failure;
    };
    WritebackOps ops;
    std::function<void(TransferFlush)> phase;
    // Keep the earliest open file description so syncfs can report errors incurred during staging.
    Volume& observe(int directory, dev_t device, bool requireSync = false);
    void pin(Volume& volume, int directory);
    void published(Volume& volume, TransferResult& result, bool copiedMove = false);
    // Re-registers a result when post-flush cleanup mutates a healthy removable volume.
    void markDirty(Volume& volume, TransferResult& result);
    void markDirty(dev_t device, TransferResult& result);
    void flush(Volume& volume, bool final = false);
    void flushPublished(dev_t device);
    void flushAllPublished();
    // Flush all outstanding publications even after cancellation or an earlier filesystem failure.
    bool finish();

  private:
    std::map<dev_t, Volume> m_volumes;
    // Btrfs subvolumes can present different st_dev values for one superblock.
    std::map<dev_t, dev_t> m_aliases;
    std::optional<std::string> m_mountinfo;
    bool m_failed = false;
  };
} // namespace luciole::transfer
