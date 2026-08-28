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
  foreach (recycle_bin_get_adapters() as $adapter) {
    if (!empty($adapter['base table']) && isset($data[$adapter['base table']]['table']['base'])) {
      if (empty($data[$adapter['base table']]['table']['base']['query_tags'])) {
        $data[$adapter['base table']]['table']['base']['query_tags'] = array();
      }
      if (!in_array('recycle_bin', $data[$adapter['base table']]['table']['base']['query_tags'])) {
        $data[$adapter['base table']]['table']['base']['query_tags'][] = 'recycle_bin';
      }
    }
  }

  if (isset($data['views_entity_node']['delete_node']['field']['handler'])) {
    $data['views_entity_node']['delete_node']['field']['handler'] = 'recycle_bin_handler_field_node_link_delete';
  }
}
