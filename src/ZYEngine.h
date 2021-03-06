/* vim:set et ts=4 sts=4:
 *
 * ibus-libzhuyin - New Zhuyin engine based on libzhuyin for IBus
 *
 * Copyright (c) 2008-2010 Peng Huang <shawn.p.huang@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#ifndef __ZY_ENGINE_H_
#define __ZY_ENGINE_H_

#include <ibus.h>

#include "ZYPointer.h"
#include "ZYLookupTable.h"
#include "ZYProperty.h"
#include "ZYEditor.h"

namespace ZY {

#define IBUS_TYPE_ZHUYIN_ENGINE	\
	(ZY::ibus_zhuyin_engine_get_type ())

GType   ibus_zhuyin_engine_get_type    (void);

class Engine {
public:
    Engine (IBusEngine *engine);
    virtual ~Engine (void);

    gboolean contentIsPassword();

    // virtual functions
    virtual gboolean processKeyEvent (guint keyval, guint keycode, guint modifiers) = 0;
    virtual void focusIn (void) = 0;
    virtual void focusOut (void);
#if IBUS_CHECK_VERSION (1, 5, 4)
    virtual void setContentType (guint purpose, guint hints);
#endif
    virtual void reset (void) = 0;
    virtual void enable (void) = 0;
    virtual void disable (void) = 0;
    virtual void pageUp (void) = 0;
    virtual void pageDown (void) = 0;
    virtual void cursorUp (void) = 0;
    virtual void cursorDown (void) = 0;
    virtual gboolean propertyActivate (const gchar *prop_name, guint prop_state) = 0;
    virtual void candidateClicked (guint index, guint button, guint state) = 0;

protected:
    void commitText (Text & text) const
    {
        ibus_engine_commit_text (m_engine, text);
    }

    void updatePreeditText (Text & text, guint cursor, gboolean visible) const
    {
        ibus_engine_update_preedit_text (m_engine, text, cursor, visible);
    }

    void showPreeditText (void) const
    {
        ibus_engine_show_preedit_text (m_engine);
    }

    void hidePreeditText (void) const
    {
        ibus_engine_hide_preedit_text (m_engine);
    }

    void updateAuxiliaryText (Text & text, gboolean visible) const
    {
        ibus_engine_update_auxiliary_text (m_engine, text, visible);
    }

    void showAuxiliaryText (void) const
    {
        ibus_engine_show_auxiliary_text (m_engine);
    }

    void hideAuxiliaryText (void) const
    {
        ibus_engine_hide_auxiliary_text (m_engine);
    }

    void updateLookupTable (LookupTable &table, gboolean visible) const
    {
        ibus_engine_update_lookup_table (m_engine, table, visible);
    }

    void updateLookupTableFast (LookupTable &table, gboolean visible) const
    {
        ibus_engine_update_lookup_table_fast (m_engine, table, visible);
    }

    void showLookupTable (void) const
    {
        ibus_engine_show_lookup_table (m_engine);
    }

    void hideLookupTable (void) const
    {
        ibus_engine_hide_lookup_table (m_engine);
    }

    void registerProperties (PropList & props) const
    {
        ibus_engine_register_properties (m_engine, props);
    }

    void updateProperty (Property & prop) const
    {
        ibus_engine_update_property (m_engine, prop);
    }

protected:
    Pointer<IBusEngine>  m_engine;      // engine pointer

#if IBUS_CHECK_VERSION (1, 5, 4)
    IBusInputPurpose m_input_purpose;
#endif

};

};
#endif
