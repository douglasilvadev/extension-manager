#include "exm-extension.h"

struct _ExmExtension
{
    GObject parent_instance;
    gchar *uuid;
    gchar *display_name;
    gchar *description;
    gboolean enabled;
    gboolean is_user;
    gboolean has_prefs;
    gboolean has_update;
};

G_DEFINE_FINAL_TYPE (ExmExtension, exm_extension, G_TYPE_OBJECT)

enum {
    PROP_0,
    PROP_UUID,
    PROP_DISPLAY_NAME,
    PROP_ENABLED,
    PROP_IS_USER,
    PROP_DESCRIPTION,
    PROP_HAS_PREFS,
    PROP_HAS_UPDATE,
    N_PROPS
};

static GParamSpec *properties [N_PROPS];

ExmExtension *
exm_extension_new (gchar    *uuid,
                   gchar    *display_name,
                   gchar    *description,
                   gboolean  enabled,
                   gboolean  is_user,
                   gboolean  has_prefs,
                   gboolean  has_update)
{
    return g_object_new (EXM_TYPE_EXTENSION,
                         "uuid", uuid,
                         "display-name", display_name,
                         "description", description,
                         "enabled", enabled,
                         "is-user", is_user,
                         "has-prefs", has_prefs,
                         "has-update", has_update,
                         NULL);
}

static void
exm_extension_finalize (GObject *object)
{
    ExmExtension *self = (ExmExtension *)object;

    G_OBJECT_CLASS (exm_extension_parent_class)->finalize (object);
}

static void
exm_extension_get_property (GObject    *object,
                            guint       prop_id,
                            GValue     *value,
                            GParamSpec *pspec)
{
    ExmExtension *self = EXM_EXTENSION (object);

    switch (prop_id)
    {
    case PROP_UUID:
        g_value_set_string (value, self->uuid);
        break;
    case PROP_DISPLAY_NAME:
        g_value_set_string (value, self->display_name);
        self->display_name = g_markup_escape_text (self->display_name, -1);
        break;
    case PROP_DESCRIPTION:
        g_value_set_string (value, self->description);
        self->description = g_markup_escape_text (self->description, -1);
        break;
    case PROP_ENABLED:
        g_value_set_boolean (value, self->enabled);
        break;
    case PROP_IS_USER:
        g_value_set_boolean (value, self->is_user);
        break;
    case PROP_HAS_PREFS:
        g_value_set_boolean (value, self->has_prefs);
        break;
    case PROP_HAS_UPDATE:
        g_value_set_boolean (value, self->has_update);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
exm_extension_set_property (GObject      *object,
                            guint         prop_id,
                            const GValue *value,
                            GParamSpec   *pspec)
{
    ExmExtension *self = EXM_EXTENSION (object);

    switch (prop_id)
    {
    case PROP_UUID:
        self->uuid = g_value_dup_string (value);
        break;
    case PROP_DISPLAY_NAME:
        self->display_name = g_value_dup_string (value);
        break;
    case PROP_DESCRIPTION:
        self->description = g_value_dup_string (value);
        break;
    case PROP_ENABLED:
        self->enabled = g_value_get_boolean (value);
        break;
    case PROP_IS_USER:
        self->is_user = g_value_get_boolean (value);
        break;
    case PROP_HAS_PREFS:
        self->has_prefs = g_value_get_boolean (value);
        break;
    case PROP_HAS_UPDATE:
        self->has_update = g_value_get_boolean (value);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
exm_extension_class_init (ExmExtensionClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    object_class->finalize = exm_extension_finalize;
    object_class->get_property = exm_extension_get_property;
    object_class->set_property = exm_extension_set_property;

    properties [PROP_UUID] =
        g_param_spec_string ("uuid",
                             "UUID",
                             "UUID",
                             NULL,
                             G_PARAM_READWRITE|G_PARAM_CONSTRUCT_ONLY);

    properties [PROP_DISPLAY_NAME] =
        g_param_spec_string ("display-name",
                             "Display Name",
                             "Display Name",
                             NULL,
                             G_PARAM_READWRITE|G_PARAM_CONSTRUCT_ONLY);

    properties [PROP_DESCRIPTION] =
        g_param_spec_string ("description",
                             "Description",
                             "Description",
                             NULL,
                             G_PARAM_READWRITE|G_PARAM_CONSTRUCT_ONLY);

    properties [PROP_ENABLED] =
        g_param_spec_boolean ("enabled",
                              "Enabled",
                              "Enabled",
                              FALSE,
                              G_PARAM_READWRITE|G_PARAM_CONSTRUCT);

    properties [PROP_IS_USER] =
        g_param_spec_boolean ("is-user",
                              "Is User",
                              "Is User",
                              FALSE,
                              G_PARAM_READWRITE|G_PARAM_CONSTRUCT);

    properties [PROP_HAS_PREFS] =
        g_param_spec_boolean ("has-prefs",
                              "Has Preferences",
                              "Has Preferences",
                              FALSE,
                              G_PARAM_READWRITE|G_PARAM_CONSTRUCT_ONLY);

    properties [PROP_HAS_UPDATE] =
        g_param_spec_boolean ("has-update",
                              "Has Update",
                              "Has Update",
                              FALSE,
                              G_PARAM_READWRITE|G_PARAM_CONSTRUCT_ONLY);

    g_object_class_install_properties (object_class, N_PROPS, properties);
}

static void
exm_extension_init (ExmExtension *self)
{
}
