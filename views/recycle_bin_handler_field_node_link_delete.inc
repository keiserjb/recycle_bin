<?php
/**
 * @file
 * Definition of recycle_bin_handler_field_node_link_delete.
 */

/**
 * Field handler to present a link to delete a node, labeled contextually
 * for content types that will be soft-deleted to the Recycle Bin.
 *
 * @ingroup views_field_handlers
 */
class recycle_bin_handler_field_node_link_delete extends views_handler_field_node_link_delete {

  /**
   * Renders the link.
   */
  function render_link($node, $values) {
    // Ensure user has access to delete this node.
    if (!node_access('delete', $node)) {
      return;
    }

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = "node/$node->nid/delete";
    $this->options['alter']['query'] = backdrop_get_destination();

    if (!empty($this->options['text'])) {
      return $this->options['text'];
    }

    return recycle_bin_node_will_soft_delete($node) ? t('Move to Bin') : t('Delete');
  }
}
