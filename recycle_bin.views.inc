<?php

/**
 * @file
 * Views data integration for Recycle Bin.
 */

/**
 * Implements hook_views_data_alter().
 *
 * Swaps in a delete-link field handler that labels the link "Move to Bin"
 * for nodes whose type is opted into the Recycle Bin, instead of always
 * showing "Delete" on admin/content regardless of what will actually happen.
 */
function recycle_bin_views_data_alter(&$data) {
  if (isset($data['views_entity_node']['delete_node']['field']['handler'])) {
    $data['views_entity_node']['delete_node']['field']['handler'] = 'recycle_bin_handler_field_node_link_delete';
  }
}
