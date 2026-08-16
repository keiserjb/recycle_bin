<?php

/**
 * @file
 * Views query tagging for Recycle Bin.
 */

/**
 * Implements hook_views_query_alter().
 */
function recycle_bin_views_query_alter(&$view, &$query) {
  if (recycle_bin_context() === 'ignore') {
    return;
  }
  foreach (recycle_bin_get_adapters() as $adapter) {
    if ($view->base_table === $adapter['base table']) {
      $query->add_tag('recycle_bin');
      return;
    }
  }
}
