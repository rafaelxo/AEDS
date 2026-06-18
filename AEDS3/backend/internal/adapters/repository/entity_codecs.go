package repository

import (
	"backend/internal/crypto"
	"backend/internal/domain"
	"bytes"
	"encoding/binary"
	"encoding/json"
	"fmt"
	"io"
)

const (
	payloadVersion                  = uint8(4)
	payloadVersionV3                = uint8(3)
	entityTypeProperty              = 1
	entityTypeUser                  = 2
	entityTypeReservation           = 3
	entityTypeAmenity               = 4
	propertyFieldIDID               = 1
	propertyFieldIDUserID           = 2
	propertyFieldIDTitle            = 3
	propertyFieldIDDescription      = 4
	propertyFieldIDCity             = 5
	propertyFieldIDDailyRate        = 6
	propertyFieldIDCreatedAt        = 7
	propertyFieldIDPhotos           = 8
	propertyFieldIDActive           = 9
	propertyFieldIDAddress          = 10
	propertyFieldIDAmenities        = 11
	propertyFieldIDLatitude         = 12
	propertyFieldIDLongitude        = 13
	userFieldIDID                   = 1
	userFieldIDName                 = 2
	userFieldIDEmail                = 3
	userFieldIDPassword             = 4
	userFieldIDType                 = 5
	userFieldIDActive               = 6
	userFieldIDPhone                = 7
	reservationFieldIDID            = 1
	reservationFieldIDPropertyID    = 2
	reservationFieldIDGuestID       = 3
	reservationFieldIDStartDate     = 4
	reservationFieldIDEndDate       = 5
	reservationFieldIDTotalValue    = 6
	reservationFieldIDStatus        = 7
	reservationFieldIDPaymentMethod = 8
	reservationFieldIDPaymentStatus = 9
	reservationFieldIDConfirmedAt   = 10
	amenityFieldIDName              = 1
	amenityFieldIDDescription       = 2
	amenityFieldIDIcon              = 3
	amenityFieldIDActive            = 4
	userTypeAdmin                   = uint8(1)
	userTypeHost                    = uint8(2)
	userTypeGuest                   = uint8(3)
)

type recordField struct {
	id   uint8
	data []byte
}

func propertyPayloadCodec() payloadCodec[domain.Property] {
	return payloadCodec[domain.Property]{
		encode: encodeProperty,
		decode: decodeProperty,
	}
}

func userPayloadCodec() payloadCodec[domain.User] {
	return payloadCodec[domain.User]{
		encode: encodeUser,
		decode: decodeUser,
	}
}

func reservationPayloadCodec() payloadCodec[domain.Reservation] {
	return payloadCodec[domain.Reservation]{
		encode: encodeReservation,
		decode: decodeReservation,
	}
}

func amenityPayloadCodec() payloadCodec[domain.AmenityCatalogItem] {
	return payloadCodec[domain.AmenityCatalogItem]{
		encode: encodeAmenity,
		decode: decodeAmenity,
	}
}

func encodeProperty(item domain.Property) ([]byte, error) {
	fields := make([]recordField, 0, 12)

	userIDData, err := encodeInt32Data(int32(item.UserID))
	if err != nil {
		return nil, err
	}
	fields = append(fields, recordField{id: propertyFieldIDUserID, data: userIDData})

	fields = append(fields, recordField{id: propertyFieldIDTitle, data: []byte(item.Title)})
	fields = append(fields, recordField{id: propertyFieldIDDescription, data: []byte(item.Description)})
	fields = append(fields, recordField{id: propertyFieldIDCity, data: []byte(item.City)})

	latitudeData, err := encodeFloat64Data(item.Latitude)
	if err != nil {
		return nil, err
	}
	fields = append(fields, recordField{id: propertyFieldIDLatitude, data: latitudeData})

	longitudeData, err := encodeFloat64Data(item.Longitude)
	if err != nil {
		return nil, err
	}
	fields = append(fields, recordField{id: propertyFieldIDLongitude, data: longitudeData})

	dailyRateData, err := encodeFloat64Data(item.DailyRate)
	if err != nil {
		return nil, err
	}
	fields = append(fields, recordField{id: propertyFieldIDDailyRate, data: dailyRateData})

	fields = append(fields, recordField{id: propertyFieldIDCreatedAt, data: []byte(item.CreatedAt)})

	photosData, err := encodeStringListData(item.Photos)
	if err != nil {
		return nil, err
	}
	fields = append(fields, recordField{id: propertyFieldIDPhotos, data: photosData})

	activeData, err := encodeBoolData(item.Active)
	if err != nil {
		return nil, err
	}
	fields = append(fields, recordField{id: propertyFieldIDActive, data: activeData})

	addressData, err := encodeAddressData(item.Address)
	if err != nil {
		return nil, err
	}
	fields = append(fields, recordField{id: propertyFieldIDAddress, data: addressData})

	amenitiesData, err := encodeAmenitiesData(item.Amenities)
	if err != nil {
		return nil, err
	}
	fields = append(fields, recordField{id: propertyFieldIDAmenities, data: amenitiesData})

	return encodeStandardPayload(entityTypeProperty, fields)
}

func decodeProperty(payload []byte, id int) (domain.Property, error) {
	fields, err := decodeStandardPayload(payload, entityTypeProperty)
	if err == nil {
		return decodePropertyFromStandard(fields, id)
	}
	return decodePropertyLegacy(payload, id)
}

func decodePropertyFromStandard(fields map[uint8][]byte, id int) (domain.Property, error) {
	var item domain.Property
	item.ID = id

	userIDData, err := requiredField(fields, propertyFieldIDUserID)
	if err != nil {
		return domain.Property{}, err
	}
	userID, err := decodeInt32Data(userIDData)
	if err != nil {
		return domain.Property{}, err
	}
	item.UserID = int(userID)

	titleData, err := requiredField(fields, propertyFieldIDTitle)
	if err != nil {
		return domain.Property{}, err
	}
	item.Title = string(titleData)

	descriptionData, err := requiredField(fields, propertyFieldIDDescription)
	if err != nil {
		return domain.Property{}, err
	}
	item.Description = string(descriptionData)

	cityData, err := requiredField(fields, propertyFieldIDCity)
	if err != nil {
		return domain.Property{}, err
	}
	item.City = string(cityData)

	if latitudeData, ok := optionalField(fields, propertyFieldIDLatitude); ok {
		item.Latitude, err = decodeFloat64Data(latitudeData)
		if err != nil {
			return domain.Property{}, err
		}
	}

	if longitudeData, ok := optionalField(fields, propertyFieldIDLongitude); ok {
		item.Longitude, err = decodeFloat64Data(longitudeData)
		if err != nil {
			return domain.Property{}, err
		}
	}

	dailyRateData, err := requiredField(fields, propertyFieldIDDailyRate)
	if err != nil {
		return domain.Property{}, err
	}
	item.DailyRate, err = decodeFloat64Data(dailyRateData)
	if err != nil {
		return domain.Property{}, err
	}

	createdAtData, err := requiredField(fields, propertyFieldIDCreatedAt)
	if err != nil {
		return domain.Property{}, err
	}
	item.CreatedAt = string(createdAtData)

	photosData, err := requiredField(fields, propertyFieldIDPhotos)
	if err != nil {
		return domain.Property{}, err
	}
	item.Photos, err = decodeStringListData(photosData)
	if err != nil {
		return domain.Property{}, err
	}

	activeData, err := requiredField(fields, propertyFieldIDActive)
	if err != nil {
		return domain.Property{}, err
	}
	item.Active, err = decodeBoolData(activeData)
	if err != nil {
		return domain.Property{}, err
	}

	if addressData, ok := optionalField(fields, propertyFieldIDAddress); ok {
		item.Address, err = decodeAddressData(addressData)
		if err != nil {
			return domain.Property{}, err
		}
	} else {
		item.Address = domain.Address{City: item.City}
	}

	if amenitiesData, ok := optionalField(fields, propertyFieldIDAmenities); ok {
		item.Amenities, err = decodeAmenitiesData(amenitiesData)
		if err != nil {
			return domain.Property{}, err
		}
	}

	if item.Address.City == "" {
		item.Address.City = item.City
	}

	return item, nil
}

func decodePropertyLegacy(payload []byte, id int) (domain.Property, error) {
	reader := bytes.NewReader(payload)
	var item domain.Property
	item.ID = id

	if _, err := readInt32(reader); err != nil {
		return domain.Property{}, err
	}

	userID, err := readInt32(reader)
	if err != nil {
		return domain.Property{}, err
	}
	item.UserID = int(userID)

	item.Title, err = readString(reader)
	if err != nil {
		return domain.Property{}, err
	}
	item.Description, err = readString(reader)
	if err != nil {
		return domain.Property{}, err
	}
	item.City, err = readString(reader)
	if err != nil {
		return domain.Property{}, err
	}
	item.DailyRate, err = readFloat64(reader)
	if err != nil {
		return domain.Property{}, err
	}
	item.CreatedAt, err = readString(reader)
	if err != nil {
		return domain.Property{}, err
	}

	photosCount, err := readUint32(reader)
	if err != nil {
		return domain.Property{}, err
	}
	item.Photos = make([]string, 0, photosCount)
	for i := uint32(0); i < photosCount; i++ {
		photo, err := readString(reader)
		if err != nil {
			return domain.Property{}, err
		}
		item.Photos = append(item.Photos, photo)
	}

	item.Active, err = readBool(reader)
	if err != nil {
		return domain.Property{}, err
	}

	item.Address = domain.Address{City: item.City}
	item.Latitude = 0
	item.Longitude = 0

	return item, nil
}

func encodeUser(item domain.User) ([]byte, error) {
	fields := make([]recordField, 0, 6)

	fields = append(fields, recordField{id: userFieldIDName, data: []byte(item.Name)})
	fields = append(fields, recordField{id: userFieldIDEmail, data: []byte(item.Email)})
	fields = append(fields, recordField{id: userFieldIDPassword, data: []byte(crypto.Encrypt(item.Password, crypto.DefaultKey))})

	var typeEnum uint8
	switch item.Type {
	case domain.UserTypeAdmin:
		typeEnum = userTypeAdmin
	case domain.UserTypeHost:
		typeEnum = userTypeHost
	default:
		typeEnum = userTypeGuest
	}
	fields = append(fields, recordField{id: userFieldIDType, data: []byte{typeEnum}})

	activeData, err := encodeBoolData(item.Active)
	if err != nil {
		return nil, err
	}
	fields = append(fields, recordField{id: userFieldIDActive, data: activeData})
	fields = append(fields, recordField{id: userFieldIDPhone, data: []byte(item.Phone)})

	return encodeStandardPayload(entityTypeUser, fields)
}

func decodeUser(payload []byte, id int) (domain.User, error) {
	fields, err := decodeStandardPayload(payload, entityTypeUser)
	if err == nil {
		return decodeUserFromStandard(fields, id)
	}
	return decodeUserLegacy(payload, id)
}

func decodeUserFromStandard(fields map[uint8][]byte, id int) (domain.User, error) {
	var item domain.User
	item.ID = id

	nameData, err := requiredField(fields, userFieldIDName)
	if err != nil {
		return domain.User{}, err
	}
	item.Name = string(nameData)

	emailData, err := requiredField(fields, userFieldIDEmail)
	if err != nil {
		return domain.User{}, err
	}
	item.Email = string(emailData)

	passwordData, err := requiredField(fields, userFieldIDPassword)
	if err != nil {
		return domain.User{}, err
	}
	item.Password = crypto.Decrypt(string(passwordData), crypto.DefaultKey)

	typeData, err := requiredField(fields, userFieldIDType)
	if err != nil {
		return domain.User{}, err
	}
	if len(typeData) == 1 {
		switch typeData[0] {
		case userTypeAdmin:
			item.Type = domain.UserTypeAdmin
		case userTypeHost:
			item.Type = domain.UserTypeHost
		default:
			item.Type = domain.UserTypeGuest
		}
	} else {
		item.Type = domain.UserType(string(typeData))
	}

	activeData, err := requiredField(fields, userFieldIDActive)
	if err != nil {
		return domain.User{}, err
	}
	item.Active, err = decodeBoolData(activeData)
	if err != nil {
		return domain.User{}, err
	}

	if phoneData, ok := optionalField(fields, userFieldIDPhone); ok {
		item.Phone = string(phoneData)
	}

	return item, nil
}

func decodeUserLegacy(payload []byte, id int) (domain.User, error) {
	reader := bytes.NewReader(payload)
	var item domain.User
	item.ID = id

	if _, err := readInt32(reader); err != nil {
		return domain.User{}, err
	}

	var err error
	item.Name, err = readString(reader)
	if err != nil {
		return domain.User{}, err
	}
	item.Email, err = readString(reader)
	if err != nil {
		return domain.User{}, err
	}
	rawPassword, err := readString(reader)
	if err != nil {
		return domain.User{}, err
	}
	item.Password = crypto.Decrypt(rawPassword, crypto.DefaultKey)
	t, err := readString(reader)
	if err != nil {
		return domain.User{}, err
	}
	item.Type = domain.UserType(t)
	item.Active, err = readBool(reader)
	if err != nil {
		return domain.User{}, err
	}
	item.Phone = ""

	return item, nil
}

func encodeReservation(item domain.Reservation) ([]byte, error) {
	fields := make([]recordField, 0, 9)

	propertyIDData, err := encodeInt32Data(int32(item.PropertyID))
	if err != nil {
		return nil, err
	}
	fields = append(fields, recordField{id: reservationFieldIDPropertyID, data: propertyIDData})

	guestIDData, err := encodeInt32Data(int32(item.GuestID))
	if err != nil {
		return nil, err
	}
	fields = append(fields, recordField{id: reservationFieldIDGuestID, data: guestIDData})

	fields = append(fields, recordField{id: reservationFieldIDStartDate, data: []byte(item.StartDate)})
	fields = append(fields, recordField{id: reservationFieldIDEndDate, data: []byte(item.EndDate)})

	totalValueData, err := encodeFloat64Data(item.TotalValue)
	if err != nil {
		return nil, err
	}
	fields = append(fields, recordField{id: reservationFieldIDTotalValue, data: totalValueData})
	fields = append(fields, recordField{id: reservationFieldIDStatus, data: []byte(item.Status)})
	fields = append(fields, recordField{id: reservationFieldIDPaymentMethod, data: []byte(item.PaymentMethod)})
	fields = append(fields, recordField{id: reservationFieldIDPaymentStatus, data: []byte(item.PaymentStatus)})
	fields = append(fields, recordField{id: reservationFieldIDConfirmedAt, data: []byte(item.ConfirmedAt)})

	return encodeStandardPayload(entityTypeReservation, fields)
}

func decodeReservation(payload []byte, id int) (domain.Reservation, error) {
	fields, err := decodeStandardPayload(payload, entityTypeReservation)
	if err == nil {
		return decodeReservationFromStandard(fields, id)
	}
	return decodeReservationLegacy(payload, id)
}

func decodeReservationFromStandard(fields map[uint8][]byte, id int) (domain.Reservation, error) {
	var item domain.Reservation
	item.ID = id

	propertyIDData, err := requiredField(fields, reservationFieldIDPropertyID)
	if err != nil {
		return domain.Reservation{}, err
	}
	propertyID, err := decodeInt32Data(propertyIDData)
	if err != nil {
		return domain.Reservation{}, err
	}
	item.PropertyID = int(propertyID)

	guestIDData, err := requiredField(fields, reservationFieldIDGuestID)
	if err != nil {
		return domain.Reservation{}, err
	}
	guestID, err := decodeInt32Data(guestIDData)
	if err != nil {
		return domain.Reservation{}, err
	}
	item.GuestID = int(guestID)

	startDateData, err := requiredField(fields, reservationFieldIDStartDate)
	if err != nil {
		return domain.Reservation{}, err
	}
	item.StartDate = string(startDateData)

	endDateData, err := requiredField(fields, reservationFieldIDEndDate)
	if err != nil {
		return domain.Reservation{}, err
	}
	item.EndDate = string(endDateData)

	totalValueData, err := requiredField(fields, reservationFieldIDTotalValue)
	if err != nil {
		return domain.Reservation{}, err
	}
	item.TotalValue, err = decodeFloat64Data(totalValueData)
	if err != nil {
		return domain.Reservation{}, err
	}

	if statusData, ok := optionalField(fields, reservationFieldIDStatus); ok {
		item.Status = domain.ReservationStatus(string(statusData))
	}
	if paymentMethodData, ok := optionalField(fields, reservationFieldIDPaymentMethod); ok {
		item.PaymentMethod = domain.PaymentMethod(string(paymentMethodData))
	}
	if paymentStatusData, ok := optionalField(fields, reservationFieldIDPaymentStatus); ok {
		item.PaymentStatus = domain.PaymentStatus(string(paymentStatusData))
	}
	if confirmedAtData, ok := optionalField(fields, reservationFieldIDConfirmedAt); ok {
		item.ConfirmedAt = string(confirmedAtData)
	}

	item.SetDefaults()

	return item, nil
}

func decodeReservationLegacy(payload []byte, id int) (domain.Reservation, error) {
	reader := bytes.NewReader(payload)
	var item domain.Reservation
	item.ID = id

	if _, err := readInt32(reader); err != nil {
		return domain.Reservation{}, err
	}

	propertyID, err := readInt32(reader)
	if err != nil {
		return domain.Reservation{}, err
	}
	item.PropertyID = int(propertyID)

	guestID, err := readInt32(reader)
	if err != nil {
		return domain.Reservation{}, err
	}
	item.GuestID = int(guestID)

	item.StartDate, err = readString(reader)
	if err != nil {
		return domain.Reservation{}, err
	}
	item.EndDate, err = readString(reader)
	if err != nil {
		return domain.Reservation{}, err
	}
	item.TotalValue, err = readFloat64(reader)
	if err != nil {
		return domain.Reservation{}, err
	}

	item.SetDefaults()

	return item, nil
}

func encodeAmenity(item domain.AmenityCatalogItem) ([]byte, error) {
	fields := make([]recordField, 0, 4)
	fields = append(fields, recordField{id: amenityFieldIDName, data: []byte(item.Name)})
	fields = append(fields, recordField{id: amenityFieldIDDescription, data: []byte(item.Description)})
	fields = append(fields, recordField{id: amenityFieldIDIcon, data: []byte(item.Icon)})

	activeData, err := encodeBoolData(item.Active)
	if err != nil {
		return nil, err
	}
	fields = append(fields, recordField{id: amenityFieldIDActive, data: activeData})

	return encodeStandardPayload(entityTypeAmenity, fields)
}

func decodeAmenity(payload []byte, id int) (domain.AmenityCatalogItem, error) {
	fields, err := decodeStandardPayload(payload, entityTypeAmenity)
	if err != nil {
		return domain.AmenityCatalogItem{}, err
	}

	nameData, err := requiredField(fields, amenityFieldIDName)
	if err != nil {
		return domain.AmenityCatalogItem{}, err
	}

	descData, _ := optionalField(fields, amenityFieldIDDescription)
	iconData, _ := optionalField(fields, amenityFieldIDIcon)

	item := domain.AmenityCatalogItem{
		ID:          id,
		Name:        string(nameData),
		Description: string(descData),
		Icon:        string(iconData),
		Active:      true,
	}

	if activeData, ok := optionalField(fields, amenityFieldIDActive); ok {
		item.Active, err = decodeBoolData(activeData)
		if err != nil {
			return domain.AmenityCatalogItem{}, err
		}
	}

	return item, nil
}

func encodeStandardPayload(entityType uint8, fields []recordField) ([]byte, error) {
	if len(fields) > int(^uint16(0)) {
		return nil, fmt.Errorf("quantidade de campos excede limite")
	}

	buf := &bytes.Buffer{}
	if err := buf.WriteByte(payloadVersion); err != nil {
		return nil, err
	}
	if err := buf.WriteByte(entityType); err != nil {
		return nil, err
	}
	if err := writeUint16(buf, uint16(len(fields))); err != nil {
		return nil, err
	}

	for _, field := range fields {
		if err := buf.WriteByte(field.id); err != nil {
			return nil, err
		}
		if err := writeUint32(buf, uint32(len(field.data))); err != nil {
			return nil, err
		}
		if _, err := buf.Write(field.data); err != nil {
			return nil, err
		}
	}

	return buf.Bytes(), nil
}

func decodeStandardPayload(payload []byte, expectedEntityType uint8) (map[uint8][]byte, error) {
	if len(payload) == 0 {
		return nil, fmt.Errorf("payload vazio")
	}
	if payload[0] == 'H' {
		return decodeHST1Payload(payload, expectedEntityType)
	}
	version := payload[0]
	if version != payloadVersion && version != payloadVersionV3 {
		return nil, fmt.Errorf("formato legado")
	}

	reader := bytes.NewReader(payload)
	reader.ReadByte()

	entityType, err := reader.ReadByte()
	if err != nil {
		return nil, err
	}
	if entityType != expectedEntityType {
		return nil, fmt.Errorf("tipo de entidade invalido")
	}

	fieldCount, err := readUint16(reader)
	if err != nil {
		return nil, err
	}

	fields := make(map[uint8][]byte, fieldCount)
	for i := uint16(0); i < fieldCount; i++ {
		fieldID, err := reader.ReadByte()
		if err != nil {
			return nil, err
		}

		var size uint32
		if version == payloadVersionV3 {
			s, err := readUint16(reader)
			if err != nil {
				return nil, err
			}
			size = uint32(s)
		} else {
			size, err = readUint32(reader)
			if err != nil {
				return nil, err
			}
		}
		if uint64(size) > uint64(reader.Len()) {
			return nil, fmt.Errorf("tamanho de campo invalido")
		}

		data := make([]byte, size)
		if _, err := io.ReadFull(reader, data); err != nil {
			return nil, err
		}
		fields[fieldID] = data
	}

	return fields, nil
}

func decodeHST1Payload(payload []byte, expectedEntityType uint8) (map[uint8][]byte, error) {
	reader := bytes.NewReader(payload)

	magic := make([]byte, 4)
	if _, err := io.ReadFull(reader, magic); err != nil {
		return nil, err
	}
	if string(magic) != "HST1" {
		return nil, fmt.Errorf("payload em formato legado")
	}

	entityType, err := reader.ReadByte()
	if err != nil {
		return nil, err
	}
	if entityType != expectedEntityType {
		return nil, fmt.Errorf("tipo de entidade invalido")
	}

	fieldCount, err := readUint16(reader)
	if err != nil {
		return nil, err
	}

	fields := make(map[uint8][]byte, fieldCount)
	for i := uint16(0); i < fieldCount; i++ {
		fieldID, err := reader.ReadByte()
		if err != nil {
			return nil, err
		}

		size, err := readUint32(reader)
		if err != nil {
			return nil, err
		}
		if uint64(size) > uint64(reader.Len()) {
			return nil, fmt.Errorf("tamanho de campo invalido")
		}

		data := make([]byte, size)
		if _, err := io.ReadFull(reader, data); err != nil {
			return nil, err
		}
		fields[fieldID] = data
	}

	return fields, nil
}

func requiredField(fields map[uint8][]byte, id uint8) ([]byte, error) {
	value, ok := fields[id]
	if !ok {
		return nil, fmt.Errorf("campo %d ausente", id)
	}
	return value, nil
}

func optionalField(fields map[uint8][]byte, id uint8) ([]byte, bool) {
	value, ok := fields[id]
	return value, ok
}

func encodeAddressData(value domain.Address) ([]byte, error) {
	buf := &bytes.Buffer{}
	if err := writeString(buf, value.Street); err != nil {
		return nil, err
	}
	if err := writeString(buf, value.Number); err != nil {
		return nil, err
	}
	if err := writeString(buf, value.Neighborhood); err != nil {
		return nil, err
	}
	if err := writeString(buf, value.City); err != nil {
		return nil, err
	}
	if err := writeString(buf, value.State); err != nil {
		return nil, err
	}
	if err := writeString(buf, value.ZipCode); err != nil {
		return nil, err
	}
	return buf.Bytes(), nil
}

func decodeAddressData(data []byte) (domain.Address, error) {
	if len(data) == 0 {
		return domain.Address{}, nil
	}

	if data[0] == '{' {
		var legacy domain.Address
		if err := json.Unmarshal(data, &legacy); err != nil {
			return domain.Address{}, err
		}
		return legacy, nil
	}

	reader := bytes.NewReader(data)
	street, err := readString(reader)
	if err != nil {
		return domain.Address{}, err
	}
	number, err := readString(reader)
	if err != nil {
		return domain.Address{}, err
	}
	neighborhood, err := readString(reader)
	if err != nil {
		return domain.Address{}, err
	}
	city, err := readString(reader)
	if err != nil {
		return domain.Address{}, err
	}
	state, err := readString(reader)
	if err != nil {
		return domain.Address{}, err
	}
	zipCode, err := readString(reader)
	if err != nil {
		return domain.Address{}, err
	}

	if reader.Len() > 0 {
		_, err = readString(reader)
		if err != nil {
			if err != io.EOF && err != io.ErrUnexpectedEOF {
				return domain.Address{}, err
			}
		}
	}

	return domain.Address{
		Street:       street,
		Number:       number,
		Neighborhood: neighborhood,
		City:         city,
		State:        state,
		ZipCode:      zipCode,
	}, nil
}

func encodeAmenitiesData(values []domain.Amenity) ([]byte, error) {
	buf := &bytes.Buffer{}
	if err := writeUint32(buf, uint32(len(values))); err != nil {
		return nil, err
	}

	for _, amenity := range values {
		if err := writeString(buf, amenity.Name); err != nil {
			return nil, err
		}
		buf.WriteByte(';')
		if err := writeString(buf, amenity.Description); err != nil {
			return nil, err
		}
		buf.WriteByte(';')
	}

	return buf.Bytes(), nil
}

func decodeAmenitiesData(data []byte) ([]domain.Amenity, error) {
	if len(data) == 0 {
		return []domain.Amenity{}, nil
	}

	if data[0] == '[' {
		var legacy []domain.Amenity
		if err := json.Unmarshal(data, &legacy); err != nil {
			return nil, err
		}
		return legacy, nil
	}

	reader := bytes.NewReader(data)
	count, err := readUint32(reader)
	if err != nil {
		return nil, err
	}

	values := make([]domain.Amenity, 0, count)
	for i := uint32(0); i < count; i++ {
		name, err := readString(reader)
		if err != nil {
			return nil, err
		}
		if b, err := reader.ReadByte(); err == nil && b != ';' {
			_ = reader.UnreadByte()
		}
		description, err := readString(reader)
		if err != nil {
			return nil, err
		}
		if b, err := reader.ReadByte(); err == nil && b != ';' {
			_ = reader.UnreadByte()
		}
		values = append(values, domain.Amenity{Name: name, Description: description})
	}

	return values, nil
}

func encodeStringListData(values []string) ([]byte, error) {
	buf := &bytes.Buffer{}
	if err := writeUint32(buf, uint32(len(values))); err != nil {
		return nil, err
	}

	for _, value := range values {
		if err := writeString(buf, value); err != nil {
			return nil, err
		}
		buf.WriteByte(';')
	}

	return buf.Bytes(), nil
}

func decodeStringListData(data []byte) ([]string, error) {
	reader := bytes.NewReader(data)
	count, err := readUint32(reader)
	if err != nil {
		return nil, err
	}

	values := make([]string, 0, count)
	for i := uint32(0); i < count; i++ {
		value, err := readString(reader)
		if err != nil {
			return nil, err
		}
		values = append(values, value)
		if b, err := reader.ReadByte(); err == nil && b != ';' {
			_ = reader.UnreadByte()
		}
	}

	return values, nil
}

func encodeBoolData(value bool) ([]byte, error) {
	buf := &bytes.Buffer{}
	if err := writeBool(buf, value); err != nil {
		return nil, err
	}
	return buf.Bytes(), nil
}

func decodeBoolData(data []byte) (bool, error) {
	reader := bytes.NewReader(data)
	return readBool(reader)
}

func encodeInt32Data(value int32) ([]byte, error) {
	buf := &bytes.Buffer{}
	if err := writeInt32(buf, value); err != nil {
		return nil, err
	}
	return buf.Bytes(), nil
}

func decodeInt32Data(data []byte) (int32, error) {
	reader := bytes.NewReader(data)
	return readInt32(reader)
}

func encodeFloat64Data(value float64) ([]byte, error) {
	buf := &bytes.Buffer{}
	if err := writeFloat64(buf, value); err != nil {
		return nil, err
	}
	return buf.Bytes(), nil
}

func decodeFloat64Data(data []byte) (float64, error) {
	reader := bytes.NewReader(data)
	return readFloat64(reader)
}

func writeString(buf *bytes.Buffer, value string) error {
	bytesValue := []byte(value)
	if err := writeUint32(buf, uint32(len(bytesValue))); err != nil {
		return err
	}
	_, err := buf.Write(bytesValue)
	return err
}

func readString(reader *bytes.Reader) (string, error) {
	size, err := readUint32(reader)
	if err != nil {
		return "", err
	}

	if uint64(size) > uint64(reader.Len()) {
		return "", fmt.Errorf("tamanho de string invalido")
	}

	data := make([]byte, size)
	if _, err := reader.Read(data); err != nil {
		return "", err
	}

	return string(data), nil
}

func writeBool(buf *bytes.Buffer, value bool) error {
	if value {
		return buf.WriteByte(1)
	}
	return buf.WriteByte(0)
}

func readBool(reader *bytes.Reader) (bool, error) {
	value, err := reader.ReadByte()
	if err != nil {
		return false, err
	}
	return value == 1, nil
}

func writeInt32(buf *bytes.Buffer, value int32) error {
	return binary.Write(buf, binary.LittleEndian, value)
}

func readInt32(reader *bytes.Reader) (int32, error) {
	var value int32
	if err := binary.Read(reader, binary.LittleEndian, &value); err != nil {
		return 0, err
	}
	return value, nil
}

func writeUint32(buf *bytes.Buffer, value uint32) error {
	return binary.Write(buf, binary.LittleEndian, value)
}

func writeUint16(buf *bytes.Buffer, value uint16) error {
	return binary.Write(buf, binary.LittleEndian, value)
}

func readUint32(reader *bytes.Reader) (uint32, error) {
	var value uint32
	if err := binary.Read(reader, binary.LittleEndian, &value); err != nil {
		return 0, err
	}
	return value, nil
}

func readUint16(reader *bytes.Reader) (uint16, error) {
	var value uint16
	if err := binary.Read(reader, binary.LittleEndian, &value); err != nil {
		return 0, err
	}
	return value, nil
}

func writeFloat64(buf *bytes.Buffer, value float64) error {
	return binary.Write(buf, binary.LittleEndian, value)
}

func readFloat64(reader *bytes.Reader) (float64, error) {
	var value float64
	if err := binary.Read(reader, binary.LittleEndian, &value); err != nil {
		return 0, err
	}
	return value, nil
}
