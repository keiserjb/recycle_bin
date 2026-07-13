<?php

/**
 * @file
 * Views query tagging for Recycle Bin.
 */

/**
 * Implements hook_views_query_alter().
 */
function recycle_bin_views_query_alter(&$view, &$query) {
  if ($view->base_table === 'node' && recycle_bin_context() !== 'ignore') {
    $query->add_tag('recycle_bin');
  }
}
