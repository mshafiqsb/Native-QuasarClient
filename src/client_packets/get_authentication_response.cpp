#include "stdafx.h"
#include "packets/client_packets.h"
#include <system_info.h>
#include <helpers.h>

using namespace std;
using namespace quasar::packets;

get_authentication_response_packet::get_authentication_response_packet() :
		quasar_client_packet(PACKET_GET_AUTHENTICATION_RESPONSE) {
	initialize_values();
}

vector<unsigned char> get_authentication_response_packet::serialize_packet() {
	begin_serialization();
	m_serializer.write_primitive(m_account_type);
	m_serializer.write_primitive(m_city);
	m_serializer.write_primitive(m_country);
	m_serializer.write_primitive(m_country_code);
	m_serializer.write_primitive(m_id);
	m_serializer.write_primitive(m_img_idx);
	m_serializer.write_primitive(m_os);
	m_serializer.write_primitive(m_pcname);
	m_serializer.write_primitive(m_region);
	m_serializer.write_primitive(m_tag);
	m_serializer.write_primitive(m_username);
	m_serializer.write_primitive(m_ver);
	finalize_serialization();

	return m_serializer.get_serializer_data();
}

void get_authentication_response_packet::initialize_values() {
	tools::system_info sysinf;

	m_account_type = sysinf.get_account_type();
	m_os = sysinf.get_operating_system();
	m_city = sysinf.get_city();
	m_country = sysinf.get_country();
	m_country_code = sysinf.get_country_code();
	m_id = "AEB06EC90268D849910326C067314FD8EE2B93D4F6EC3752D4970A9EFC45AF21";
	m_img_idx = 195;
	m_pcname = sysinf.get_pcname();
	m_region = sysinf.get_region();
	m_tag = "DEBUG-NATIVE";
	m_username = sysinf.get_username();
	m_ver = "1.2.0.0-N";
}