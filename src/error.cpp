#include <array>
#include <async_pqxx/error.hpp>

class async_pqxx_category : public boost::system::error_category {
public:
    [[nodiscard]] const char* name() const noexcept override { return "async_pqxx_category"; }

    [[nodiscard]] std::string message(int ev) const noexcept override {
        switch (ev) {
        case 0: return "successful_completion";
        case 1: return "warning";
        case 2: return "dynamic_result_sets_returned";
        case 3: return "implicit_zero_bit_padding";
        case 4: return "null_value_eliminated_in_set_function";
        case 5: return "privilege_not_granted";
        case 6: return "privilege_not_revoked";
        case 7: return "string_data_right_truncation";
        case 8: return "deprecated_feature";
        case 9: return "no_data";
        case 10: return "no_additional_dynamic_result_sets_returned";
        case 11: return "sql_statement_not_yet_complete";
        case 12: return "connection_exception";
        case 13: return "connection_does_not_exist";
        case 14: return "connection_failure";
        case 15: return "sqlclient_unable_to_establish_sqlconnection";
        case 16: return "sqlserver_rejected_establishment_of_sqlconnection";
        case 17: return "transaction_resolution_unknown";
        case 18: return "protocol_violation";
        case 19: return "triggered_action_exception";
        case 20: return "feature_not_supported";
        case 21: return "invalid_transaction_initiation";
        case 22: return "locator_exception";
        case 23: return "invalid_locator_specification";
        case 24: return "invalid_grantor";
        case 25: return "invalid_grant_operation";
        case 26: return "invalid_role_specification";
        case 27: return "diagnostics_exception";
        case 28: return "stacked_diagnostics_accessed_without_active_handler";
        case 29: return "case_not_found";
        case 30: return "cardinality_violation";
        case 31: return "data_exception";
        case 32: return "array_subscript_error";
        case 33: return "character_not_in_repertoire";
        case 34: return "datetime_field_overflow";
        case 35: return "division_by_zero";
        case 36: return "error_in_assignment";
        case 37: return "escape_character_conflict";
        case 38: return "indicator_overflow";
        case 39: return "interval_field_overflow";
        case 40: return "invalid_argument_for_logarithm";
        case 41: return "invalid_argument_for_ntile_function";
        case 42: return "invalid_argument_for_nth_value_function";
        case 43: return "invalid_argument_for_power_function";
        case 44: return "invalid_argument_for_width_bucket_function";
        case 45: return "invalid_character_value_for_cast";
        case 46: return "invalid_datetime_format";
        case 47: return "invalid_escape_character";
        case 48: return "invalid_escape_octet";
        case 49: return "invalid_escape_sequence";
        case 50: return "nonstandard_use_of_escape_character";
        case 51: return "invalid_indicator_parameter_value";
        case 52: return "invalid_parameter_value";
        case 53: return "invalid_preceding_or_following_size";
        case 54: return "invalid_regular_expression";
        case 55: return "invalid_row_count_in_limit_clause";
        case 56: return "invalid_row_count_in_result_offset_clause";
        case 57: return "invalid_tablesample_argument";
        case 58: return "invalid_tablesample_repeat";
        case 59: return "invalid_time_zone_displacement_value";
        case 60: return "invalid_use_of_escape_character";
        case 61: return "most_specific_type_mismatch";
        case 62: return "null_value_not_allowed";
        case 63: return "null_value_no_indicator_parameter";
        case 64: return "numeric_value_out_of_range";
        case 65: return "sequence_generator_limit_exceeded";
        case 66: return "string_data_length_mismatch";
        case 67: return "string_data_right_truncation";
        case 68: return "substring_error";
        case 69: return "trim_error";
        case 70: return "unterminated_c_string";
        case 71: return "zero_length_character_string";
        case 72: return "floating_point_exception";
        case 73: return "invalid_text_representation";
        case 74: return "invalid_binary_representation";
        case 75: return "bad_copy_file_format";
        case 76: return "untranslatable_character";
        case 77: return "not_an_xml_document";
        case 78: return "invalid_xml_document";
        case 79: return "invalid_xml_content";
        case 80: return "invalid_xml_comment";
        case 81: return "invalid_xml_processing_instruction";
        case 82: return "integrity_constraint_violation";
        case 83: return "restrict_violation";
        case 84: return "not_null_violation";
        case 85: return "foreign_key_violation";
        case 86: return "unique_violation";
        case 87: return "check_violation";
        case 88: return "exclusion_violation";
        case 89: return "invalid_cursor_state";
        case 90: return "invalid_transaction_state";
        case 91: return "active_sql_transaction";
        case 92: return "branch_transaction_already_active";
        case 93: return "held_cursor_requires_same_isolation_level";
        case 94: return "inappropriate_access_mode_for_branch_transaction";
        case 95: return "inappropriate_isolation_level_for_branch_transaction";
        case 96: return "no_active_sql_transaction_for_branch_transaction";
        case 97: return "read_only_sql_transaction";
        case 98: return "schema_and_data_statement_mixing_not_supported";
        case 99: return "no_active_sql_transaction";
        case 100: return "in_failed_sql_transaction";
        case 101: return "idle_in_transaction_session_timeout";
        case 102: return "invalid_sql_statement_name";
        case 103: return "triggered_data_change_violation";
        case 104: return "invalid_authorization_specification";
        case 105: return "invalid_password";
        case 106: return "dependent_privilege_descriptors_still_exist";
        case 107: return "dependent_objects_still_exist";
        case 108: return "invalid_transaction_termination";
        case 109: return "sql_routine_exception";
        case 110: return "function_executed_no_return_statement";
        case 111: return "modifying_sql_data_not_permitted";
        case 112: return "prohibited_sql_statement_attempted";
        case 113: return "reading_sql_data_not_permitted";
        case 114: return "invalid_cursor_name";
        case 115: return "external_routine_exception";
        case 116: return "containing_sql_not_permitted";
        case 117: return "modifying_sql_data_not_permitted";
        case 118: return "prohibited_sql_statement_attempted";
        case 119: return "reading_sql_data_not_permitted";
        case 120: return "external_routine_invocation_exception";
        case 121: return "invalid_sqlstate_returned";
        case 122: return "null_value_not_allowed";
        case 123: return "trigger_protocol_violated";
        case 124: return "srf_protocol_violated";
        case 125: return "event_trigger_protocol_violated";
        case 126: return "savepoint_exception";
        case 127: return "invalid_savepoint_specification";
        case 128: return "invalid_catalog_name";
        case 129: return "invalid_schema_name";
        case 130: return "transaction_rollback";
        case 131: return "transaction_integrity_constraint_violation";
        case 132: return "serialization_failure";
        case 133: return "statement_completion_unknown";
        case 134: return "deadlock_detected";
        case 135: return "syntax_error_or_access_rule_violation";
        case 136: return "syntax_error";
        case 137: return "insufficient_privilege";
        case 138: return "cannot_coerce";
        case 139: return "grouping_error";
        case 140: return "windowing_error";
        case 141: return "invalid_recursion";
        case 142: return "invalid_foreign_key";
        case 143: return "invalid_name";
        case 144: return "name_too_long";
        case 145: return "reserved_name";
        case 146: return "datatype_mismatch";
        case 147: return "indeterminate_datatype";
        case 148: return "collation_mismatch";
        case 149: return "indeterminate_collation";
        case 150: return "wrong_object_type";
        case 151: return "generated_always";
        case 152: return "undefined_column";
        case 153: return "undefined_function";
        case 154: return "undefined_table";
        case 155: return "undefined_parameter";
        case 156: return "undefined_object";
        case 157: return "duplicate_column";
        case 158: return "duplicate_cursor";
        case 159: return "duplicate_database";
        case 160: return "duplicate_function";
        case 161: return "duplicate_prepared_statement";
        case 162: return "duplicate_schema";
        case 163: return "duplicate_table";
        case 164: return "duplicate_alias";
        case 165: return "duplicate_object";
        case 166: return "ambiguous_column";
        case 167: return "ambiguous_function";
        case 168: return "ambiguous_parameter";
        case 169: return "ambiguous_alias";
        case 170: return "invalid_column_reference";
        case 171: return "invalid_column_definition";
        case 172: return "invalid_cursor_definition";
        case 173: return "invalid_database_definition";
        case 174: return "invalid_function_definition";
        case 175: return "invalid_prepared_statement_definition";
        case 176: return "invalid_schema_definition";
        case 177: return "invalid_table_definition";
        case 178: return "invalid_object_definition";
        case 179: return "with_check_option_violation";
        case 180: return "insufficient_resources";
        case 181: return "disk_full";
        case 182: return "out_of_memory";
        case 183: return "too_many_connections";
        case 184: return "configuration_limit_exceeded";
        case 185: return "program_limit_exceeded";
        case 186: return "statement_too_complex";
        case 187: return "too_many_columns";
        case 188: return "too_many_arguments";
        case 189: return "object_not_in_prerequisite_state";
        case 190: return "object_in_use";
        case 191: return "cant_change_runtime_param";
        case 192: return "lock_not_available";
        case 193: return "operator_intervention";
        case 194: return "query_canceled";
        case 195: return "admin_shutdown";
        case 196: return "crash_shutdown";
        case 197: return "cannot_connect_now";
        case 198: return "database_dropped";
        case 199: return "system_error";
        case 200: return "io_error";
        case 201: return "undefined_file";
        case 202: return "duplicate_file";
        case 203: return "snapshot_too_old";
        case 204: return "config_file_error";
        case 205: return "lock_file_exists";
        case 206: return "fdw_error";
        case 207: return "fdw_column_name_not_found";
        case 208: return "fdw_dynamic_parameter_value_needed";
        case 209: return "fdw_function_sequence_error";
        case 210: return "fdw_inconsistent_descriptor_information";
        case 211: return "fdw_invalid_attribute_value";
        case 212: return "fdw_invalid_column_name";
        case 213: return "fdw_invalid_column_number";
        case 214: return "fdw_invalid_data_type";
        case 215: return "fdw_invalid_data_type_descriptors";
        case 216: return "fdw_invalid_descriptor_field_identifier";
        case 217: return "fdw_invalid_handle";
        case 218: return "fdw_invalid_option_index";
        case 219: return "fdw_invalid_option_name";
        case 220: return "fdw_invalid_string_length_or_buffer_length";
        case 221: return "fdw_invalid_string_format";
        case 222: return "fdw_invalid_use_of_null_pointer";
        case 223: return "fdw_too_many_handles";
        case 224: return "fdw_out_of_memory";
        case 225: return "fdw_no_schemas";
        case 226: return "fdw_option_name_not_found";
        case 227: return "fdw_reply_handle";
        case 228: return "fdw_schema_not_found";
        case 229: return "fdw_table_not_found";
        case 230: return "fdw_unable_to_create_execution";
        case 231: return "fdw_unable_to_create_reply";
        case 232: return "fdw_unable_to_establish_connection";
        case 233: return "plpgsql_error";
        case 234: return "raise_exception";
        case 235: return "no_data_found";
        case 236: return "too_many_rows";
        case 237: return "assert_failure";
        case 238: return "internal_error";
        case 239: return "data_corrupted";
        case 240: return "index_corrupted";
        default: return "unknown error";
        }
    }
};

async_pqxx_category category;

boost::system::error_category& async_pqxx::async_pqxx_category() { return category; }

constexpr std::array<std::pair<const char*, int>, 241> str_codes{
    {{"00000", 0},   {"01000", 1},   {"0100C", 2},   {"01008", 3},   {"01003", 4},   {"01007", 5},   {"01006", 6},
     {"01004", 7},   {"01P01", 8},   {"02000", 9},   {"02001", 10},  {"03000", 11},  {"08000", 12},  {"08003", 13},
     {"08006", 14},  {"08001", 15},  {"08004", 16},  {"08007", 17},  {"08P01", 18},  {"09000", 19},  {"0A000", 20},
     {"0B000", 21},  {"0F000", 22},  {"0F001", 23},  {"0L000", 24},  {"0LP01", 25},  {"0P000", 26},  {"0Z000", 27},
     {"0Z002", 28},  {"20000", 29},  {"21000", 30},  {"22000", 31},  {"2202E", 32},  {"22021", 33},  {"22008", 34},
     {"22012", 35},  {"22005", 36},  {"2200B", 37},  {"22022", 38},  {"22015", 39},  {"2201E", 40},  {"22014", 41},
     {"22016", 42},  {"2201F", 43},  {"2201G", 44},  {"22018", 45},  {"22007", 46},  {"22019", 47},  {"2200D", 48},
     {"22025", 49},  {"22P06", 50},  {"22010", 51},  {"22023", 52},  {"22013", 53},  {"2201B", 54},  {"2201W", 55},
     {"2201X", 56},  {"2202H", 57},  {"2202G", 58},  {"22009", 59},  {"2200C", 60},  {"2200G", 61},  {"22004", 62},
     {"22002", 63},  {"22003", 64},  {"2200H", 65},  {"22026", 66},  {"22001", 67},  {"22011", 68},  {"22027", 69},
     {"22024", 70},  {"2200F", 71},  {"22P01", 72},  {"22P02", 73},  {"22P03", 74},  {"22P04", 75},  {"22P05", 76},
     {"2200L", 77},  {"2200M", 78},  {"2200N", 79},  {"2200S", 80},  {"2200T", 81},  {"23000", 82},  {"23001", 83},
     {"23502", 84},  {"23503", 85},  {"23505", 86},  {"23514", 87},  {"23P01", 88},  {"24000", 89},  {"25000", 90},
     {"25001", 91},  {"25002", 92},  {"25008", 93},  {"25003", 94},  {"25004", 95},  {"25005", 96},  {"25006", 97},
     {"25007", 98},  {"25P01", 99},  {"25P02", 100}, {"25P03", 101}, {"26000", 102}, {"27000", 103}, {"28000", 104},
     {"28P01", 105}, {"2B000", 106}, {"2BP01", 107}, {"2D000", 108}, {"2F000", 109}, {"2F005", 110}, {"2F002", 111},
     {"2F003", 112}, {"2F004", 113}, {"34000", 114}, {"38000", 115}, {"38001", 116}, {"38002", 117}, {"38003", 118},
     {"38004", 119}, {"39000", 120}, {"39001", 121}, {"39004", 122}, {"39P01", 123}, {"39P02", 124}, {"39P03", 125},
     {"3B000", 126}, {"3B001", 127}, {"3D000", 128}, {"3F000", 129}, {"40000", 130}, {"40002", 131}, {"40001", 132},
     {"40003", 133}, {"40P01", 134}, {"42000", 135}, {"42601", 136}, {"42501", 137}, {"42846", 138}, {"42803", 139},
     {"42P20", 140}, {"42P19", 141}, {"42830", 142}, {"42602", 143}, {"42622", 144}, {"42939", 145}, {"42804", 146},
     {"42P18", 147}, {"42P21", 148}, {"42P22", 149}, {"42809", 150}, {"428C9", 151}, {"42703", 152}, {"42883", 153},
     {"42P01", 154}, {"42P02", 155}, {"42704", 156}, {"42701", 157}, {"42P03", 158}, {"42P04", 159}, {"42723", 160},
     {"42P05", 161}, {"42P06", 162}, {"42P07", 163}, {"42712", 164}, {"42710", 165}, {"42702", 166}, {"42725", 167},
     {"42P08", 168}, {"42P09", 169}, {"42P10", 170}, {"42611", 171}, {"42P11", 172}, {"42P12", 173}, {"42P13", 174},
     {"42P14", 175}, {"42P15", 176}, {"42P16", 177}, {"42P17", 178}, {"44000", 179}, {"53000", 180}, {"53100", 181},
     {"53200", 182}, {"53300", 183}, {"53400", 184}, {"54000", 185}, {"54001", 186}, {"54011", 187}, {"54023", 188},
     {"55000", 189}, {"55006", 190}, {"55P02", 191}, {"55P03", 192}, {"57000", 193}, {"57014", 194}, {"57P01", 195},
     {"57P02", 196}, {"57P03", 197}, {"57P04", 198}, {"58000", 199}, {"58030", 200}, {"58P01", 201}, {"58P02", 202},
     {"72000", 203}, {"F0000", 204}, {"F0001", 205}, {"HV000", 206}, {"HV005", 207}, {"HV002", 208}, {"HV010", 209},
     {"HV021", 210}, {"HV024", 211}, {"HV007", 212}, {"HV008", 213}, {"HV004", 214}, {"HV006", 215}, {"HV091", 216},
     {"HV00B", 217}, {"HV00C", 218}, {"HV00D", 219}, {"HV090", 220}, {"HV00A", 221}, {"HV009", 222}, {"HV014", 223},
     {"HV001", 224}, {"HV00P", 225}, {"HV00J", 226}, {"HV00K", 227}, {"HV00Q", 228}, {"HV00R", 229}, {"HV00L", 230},
     {"HV00M", 231}, {"HV00N", 232}, {"P0000", 233}, {"P0001", 234}, {"P0002", 235}, {"P0003", 236}, {"P0004", 237},
     {"XX000", 238}, {"XX001", 239}, {"XX002", 240}}};

boost::system::error_code async_pqxx::make_async_pqxx_error(const std::string& str_code) {
    auto itr = std::find_if(str_codes.begin(), str_codes.end(), [&](auto p) { return p.first == str_code; });
    if (itr) {
        return {itr->second, async_pqxx_category()};
    } else {
        return {242, async_pqxx_category()};
    }
}
