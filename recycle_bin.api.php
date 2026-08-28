<?php

/**
 * @file
 * API documentation for Recycle Bin integrations.
 */

/**
 * Registers an entity storage adapter with Recycle Bin.
 *
 * A contributing module must provide a replacement controller that extends
 * the entity type's original controller and uses
 * RecycleBinStorageAdapterTrait. This lets the original controller retain
 * responsibility for permanent deletion, field cleanup, revisions, and other
 * entity-specific behavior.
 *
 * @return array
 *   Keyed adapter definitions. Required keys are:
 *   - entity type: Entity type machine name.
 *   - controller class: The original controller class to replace.
 *   - replacement class: The contributor's subclass using the shared trait.
 *   - base table: SQL base table used by the default visibility query.
 *   - id key: Entity ID column on the base table.
 *
 *   Optional keys are:
 *   - bundle key: Base-table bundle column.
 *   - revision key: Base-table current revision column.
 *   - enabled callback: Callback receiving ($entity, $adapter), returning
 *     TRUE only when this entity should be soft-deleted.
 *   - cache reset callback: Callback receiving an array of entity IDs.
 *   - load query callback: Callback receiving ($query, $context, $adapter)
 *     when the default `base.<id key>` join is not sufficient.
 *   - entity id callback: Callback receiving an entity and returning its ID.
 *   - view multiple callback: Callback matching node_view_multiple(), receiving
 *     ($entities, $view_mode), for a permissioned Recycle Bin preview.
 *   - previewable: TRUE when the adapter supports a full-page preview.
 *
 * The adapter should remain disabled until the contributing module has defined
 * its own configuration and tested restore/purge and relationship semantics.
 *
 * @see RecycleBinStorageAdapterTrait
 * @see recycle_bin_entity_access()
 */
function hook_recycle_bin_adapter_info() {
  $adapters['my_entity'] = array(
    'entity type' => 'my_entity',
    'controller class' => 'MyEntityController',
    'replacement class' => 'MyModuleRecycleBinEntityController',
    'base table' => 'my_entity',
    'id key' => 'id',
    'bundle key' => 'bundle',
    'enabled callback' => 'mymodule_recycle_bin_my_entity_enabled',
  );
  return $adapters;
}

/**
 * Responds after an entity is committed to the Recycle Bin.
 *
 * @param object $entity
 *   Entity that was soft-deleted.
 * @param string $entity_type
 *   Entity type machine name.
 */
function hook_entity_recycle_bin_delete($entity, $entity_type) {
  list($entity_id) = entity_extract_ids($entity_type, $entity);
  watchdog('example', 'Entity @type @id moved to the Recycle Bin.', array(
    '@type' => $entity_type,
    '@id' => $entity_id,
  ));
}

/**
 * Responds after an entity restore is committed.
 *
 * @param object $entity
 *   Restored entity.
 * @param string $entity_type
 *   Entity type machine name.
 */
function hook_entity_recycle_bin_restore($entity, $entity_type) {
  watchdog('example', 'Entity @type restored from the Recycle Bin.', array('@type' => $entity_type));
}

/**
 * Responds after permanent entity deletion is committed.
 *
 * @param object $entity
 *   Permanently deleted entity as loaded before deletion.
 * @param string $entity_type
 *   Entity type machine name.
 */
function hook_entity_recycle_bin_purge($entity, $entity_type) {
  watchdog('example', 'Entity @type permanently deleted from the Recycle Bin.', array('@type' => $entity_type));
}

/**
 * A contributing module would then define its own replacement controller,
 * extending its real controller and using the shared trait, for example:
 *
 * @code
 * class MyModuleRecycleBinEntityController extends MyEntityController {
 *   use RecycleBinStorageAdapterTrait;
 * }
 *
 * function mymodule_recycle_bin_my_entity_enabled($entity, $adapter) {
 *   return (bool) config_get('mymodule.settings', 'recycle_bin_my_entity');
 * }
 * @endcode
 */

/**
 * Entity-specific modules may expose this helper from their access hook.
 *
 * @param string $entity_type
 *   Registered entity type.
 * @param object $entity
 *   Loaded entity object.
 * @param object|null $account
 *   Account to check, or the current account.
 *
 * @return bool
 *   FALSE when the entity is soft-deleted and the account lacks the generic view
 *   permission; TRUE otherwise.
 */
