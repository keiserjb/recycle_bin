<?php

/**
 * @file
 * Shared storage behavior for registered Recycle Bin adapters.
 */

/**
 * Trait for an adapter controller supplied by a contributing module.
 *
 * The using class must extend its entity type's original storage controller.
 * This preserves the original controller's permanent delete and load behavior
 * while adding the Recycle Bin lifecycle around it.
 */
trait RecycleBinStorageAdapterTrait {

  /**
   * Overrides the original controller delete path.
   */
  public function delete($ids) {
    $entity_type = $this->recycleBinEntityType();
    $adapter = recycle_bin_get_adapter($entity_type);
    if (!$adapter || recycle_bin_context() !== 'active') {
      return parent::delete($ids);
    }

    $entities = $ids ? $this->load($ids) : FALSE;
    if (!$entities) {
      return;
    }

    $soft_delete = array();
    $permanent_delete = array();
    foreach ($entities as $id => $entity) {
      if (recycle_bin_adapter_is_enabled($adapter, $entity)) {
        $soft_delete[$id] = $entity;
      }
      else {
        $permanent_delete[] = $id;
      }
    }

    if ($soft_delete) {
      recycle_bin_soft_delete_entities($entity_type, $soft_delete, $adapter);
    }
    if ($permanent_delete) {
      parent::delete($permanent_delete);
    }
  }

  /**
   * Adds Recycle Bin visibility filtering to the original load query.
   */
  protected function buildQuery($ids, $conditions = array(), $revision_id = FALSE) {
    $query = parent::buildQuery($ids, $conditions, $revision_id);
    return recycle_bin_adapter_alter_load_query($query, $this->recycleBinEntityType());
  }

  /**
   * Returns the entity type represented by this controller.
   */
  protected function recycleBinEntityType() {
    return $this->entityType;
  }
}

