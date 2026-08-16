# Recycle Bin

Recycle Bin provides opt-in recovery for deleted Backdrop content and protects
managed files from permanent deletion. It is designed for contrib/custom
integrations and keeps Backdrop's normal permanent-delete behavior when an
item is not enabled.

## Features

- Send deleted content of selected content types to the Recycle Bin instead
  of deleting it immediately, so it can be restored.
- Optional metadata-only protection for managed files from permanent deletion.
- List, restore, and permanently delete deleted nodes and managed files
  protected from permanent deletion from the Recycle Bin administration page.
- Adapter API for custom Backdrop entity types.
- Bounded automatic permanent deletion of expired Recycle Bin items.

Recycle Bin does not move file data when a managed file is sent to the Recycle
Bin. A
known public file URL may still be reachable; this feature is a recovery and
cleanup safeguard, not an access-control or private-file mechanism.

When a node is sent to the Recycle Bin, its file-field usage remains intact so
restoring the node also restores its references. Permanently deleting the node
runs Backdrop's normal field cleanup; files with no remaining usages become
temporary and are then removed by the normal file cleanup process.

## Installation

- Install this module using the official
  [Backdrop CMS instructions](https://backdropcms.org/user-guide/modules).

## Configuration

Content types are disabled by default. Enable only content types whose delete
and restore behavior has been verified for the site.

Protection for managed files from permanent deletion is also disabled by
default. Enable it only after reviewing the metadata-only behavior and the
direct-URL limitation.

Automatic permanent deletion is disabled by default. When enabled, items past
the retention period below are deleted during cron, up to the per-run limit.

## API

Contrib and custom entity modules can register an adapter with
`hook_recycle_bin_adapter_info()` and provide a replacement controller that
extends the original controller and uses `RecycleBinStorageAdapterTrait`:

```php
function example_recycle_bin_adapter_info() {
  return array(
    'example_entity' => array(
      'entity type' => 'example_entity',
      'controller class' => 'ExampleEntityController',
      'replacement class' => 'ExampleRecycleBinEntityController',
      'base table' => 'example_entity',
      'id key' => 'id',
      'enabled callback' => 'example_recycle_bin_entity_enabled',
    ),
  );
}

class ExampleRecycleBinEntityController extends ExampleEntityController {
  use RecycleBinStorageAdapterTrait;
}
```

The integrating module owns bundle policy, relationship semantics, access
checks, cache/query overrides, and special restore or permanent-deletion
rules. Lifecycle notifications are available through
`hook_entity_recycle_bin_delete()`, `hook_entity_recycle_bin_restore()`, and
`hook_entity_recycle_bin_purge()`.

## Testing

The module includes Backdrop SimpleTest coverage for node, custom entity,
managed-file, restore, and permanent-deletion lifecycles. Run the
module's tests through the site's Backdrop test runner; unrelated global core
test discovery failures should be investigated separately from this module.

## Scope and limitations

Recycle Bin does not intercept arbitrary custom SQL, external indexes, direct
public file URLs, or configuration changes. Configuration objects such as
Views and Blocks are outside this module's scope.

## Issues and contributions

Please report reproducible bugs with the Backdrop version, module version,
enabled adapters, relevant configuration, and restore/permanent-deletion
steps. New adapters should include lifecycle tests and document ownership of
related records before being enabled by default.

## Current Maintainer

[Justin Keiser](https://github.com/keiserjb)

## Credits

- Created for Backdrop CMS by [Justin Keiser](https://github.com/keiserjb).
- Inspired by the Drupal [Trash](https://www.drupal.org/project/trash) module.
- Developed with AI assistance.

## License

This project is licensed under the GNU General Public License, version 2 or
later. See [LICENSE.txt](LICENSE.txt).
